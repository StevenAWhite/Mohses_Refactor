#include "SimulationManager.h"

#include <filesystem>

/// This module's path to the config file.
constexpr char const * simulation_manager_amm = "/sim_manager_amm.xml";
constexpr char const * simulation_manager_configuration = "/sim_manager_configuration.xml";
constexpr char const * simulation_manager_capabilities = "/sim_manager_capabilities.xml"; 

using std::chrono::milliseconds;

namespace AMM {
SimulationManager::SimulationManager(std::string dds_config_path, std::string biogears_resource_path) {

   std::string resource_path = dds_config_path;
   if ( !std::filesystem::exists( resource_path + simulation_manager_amm )){
     resource_path += "/config";
   }
   std::cout << "ASDA" << resource_path + simulation_manager_amm << std::endl;
   m_mgr = new DDSManager<SimulationManager>( resource_path + simulation_manager_amm );
   m_DDS_Configuration = Utility::read_file_to_string( resource_path + simulation_manager_configuration );
   m_DDS_Capabilities  = Utility::read_file_to_string( resource_path + simulation_manager_capabilities );
   
    
   // Initialize everything we'll need to listen for 
   m_mgr->InitializeTick();
   m_mgr->InitializeSimulationControl();
   m_mgr->InitializeOperationalDescription();
   m_mgr->InitializeStatus();
   m_mgr->InitializeModuleConfiguration();

   m_mgr->CreateTickPublisher();
   m_mgr->CreateSimulationControlPublisher();
   m_mgr->CreateOperationalDescriptionPublisher();
   m_mgr->CreateModuleConfigurationPublisher();
   m_mgr->CreateStatusPublisher();

   m_mgr->CreateSimulationControlSubscriber(this, &SimulationManager::onNewSimulationControl);

   m_uuid.id(m_mgr->GenerateUuidString());

   m_runThread = false;
}


void SimulationManager::PublishOperationalDescription() {
   AMM::OperationalDescription od;
   od.name(moduleName);
   od.model("Simulation Manager");
   od.manufacturer("Vcom3D");
   od.serial_number("1.0.0");
   od.module_id(m_uuid);
   od.module_version("1.0.0");
   od.capabilities_schema(m_DDS_Capabilities);
   od.description(
      "The Simulation Manager is a core software module that drives the simulation by publishing "
      "simulation ticks at a frequency of 50 Hz.  It operates as a simulation state engine, "
      "allowing for control of time-related functions and loading scenarios for execution.");
      m_mgr->WriteOperationalDescription(od);
   }

   void SimulationManager::PublishConfiguration() {
      AMM::ModuleConfiguration mc;
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
      mc.timestamp(ms);
      mc.module_id(m_uuid);
      mc.name(moduleName);
      mc.capabilities_configuration(m_DDS_Configuration);
      m_mgr->WriteModuleConfiguration(mc);
   }

   void SimulationManager::RunSimulation(bool doWriteTopic) {

      // TODO:
      // Remove doWriteTopic

      if (!m_runThread) {
         m_runThread = true;
         m_thread = std::thread(&SimulationManager::TickLoop, this);

         if (doWriteTopic) {
            AMM::SimulationControl simControl;
            auto ms = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            simControl.timestamp(ms);
            simControl.type(AMM::ControlType::RUN);
            m_mgr->WriteSimulationControl(simControl);
         }

         LOG_INFO << "Simulation running.";
      }
   }

   void SimulationManager::HaltSimulation(bool doWriteTopic) {
      if (m_runThread) {
         m_mutex.lock();
         m_runThread = false;
         std::this_thread::sleep_for(std::chrono::milliseconds(200));
         m_mutex.unlock();
         m_thread.detach();

         if (doWriteTopic) {
            AMM::SimulationControl simControl;
            auto ms = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            simControl.timestamp(ms);
            simControl.type(AMM::ControlType::HALT);
            m_mgr->WriteSimulationControl(simControl);
         }

         LOG_INFO << "Simulation halted.";
      }
   }

   void SimulationManager::ResetSimulation(bool doWriteTopic) {
      /// Implies both Halt then Reset.

      LOG_INFO << "Sim reset in progress.";

      this->HaltSimulation(doWriteTopic);

      m_tickCount = 0;

      if (doWriteTopic) {
         AMM::SimulationControl simControl;
         auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
         simControl.timestamp(ms);
         simControl.type(AMM::ControlType::RESET);
         m_mgr->WriteSimulationControl(simControl);
      }

      LOG_INFO << "Sim reset complete. Ready to start.";
   }

   void SimulationManager::SaveSimulation(bool doWriteTopic) {
      LOG_INFO << "Saving sim state.";

      if (doWriteTopic) {
         AMM::SimulationControl simControl;
         auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
         simControl.timestamp(ms);
         simControl.type(AMM::ControlType::SAVE);
         m_mgr->WriteSimulationControl(simControl);
      }

      LOG_INFO << "Sim state saved.";
   }

   void SimulationManager::onNewSimulationControl(AMM::SimulationControl &simControl, SampleInfo_t *info) {
      bool doWriteTopic = false;

      switch (simControl.type()) {
         case AMM::ControlType::RUN: {
            LOG_INFO << "Message recieved; Run sim.";
            RunSimulation(doWriteTopic);
            break;
         }

         case AMM::ControlType::HALT: {
            LOG_INFO << "Message recieved; Halt sim";
            HaltSimulation(doWriteTopic);
            break;
         }

         case AMM::ControlType::RESET: {
            LOG_INFO << "Message recieved; Reset sim";
            ResetSimulation(doWriteTopic);
            break;
         }

         case AMM::ControlType::SAVE: {
            LOG_INFO << "Message recieved; Save sim";
            SaveSimulation(doWriteTopic);
            break;
         }
      }
   }

   int SimulationManager::GetTickCount() { return m_tickCount; }

   bool SimulationManager::IsRunning() { return m_runThread; }

   void SimulationManager::SetSampleRate(int rate) { m_sampleRate = rate; }

   int SimulationManager::GetSampleRate() { return m_sampleRate; }

   void SimulationManager::TickLoop() {
      using frames = std::chrono::duration<int64_t, std::ratio<1, 50>>;
      auto nextFrame = std::chrono::system_clock::now();
      auto lastFrame = nextFrame - frames{1};

      while (m_runThread) {
         std::this_thread::sleep_until(nextFrame);
         m_mutex.lock();
         AMM::Tick tickInstance;
         tickInstance.frame(m_tickCount++);
         m_mgr->WriteTick(tickInstance);
         lastFrame = nextFrame;
         nextFrame += frames{1};
         m_mutex.unlock();
      }
   }

   void SimulationManager::Shutdown() {
      if (m_runThread) {
         m_runThread = false;
         std::this_thread::sleep_for(std::chrono::milliseconds(200));
         m_thread.join();
      }
   }

} // namespace AMM
