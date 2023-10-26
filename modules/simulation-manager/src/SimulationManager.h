#pragma once

#include <mohses/net.h>

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

#include <thread>
#include <chrono>

#include <mohses/Utility.h>


namespace AMM {
    class SimulationManager {

    public:
        SimulationManager(std::string dds_config_path = "./", std::string biogears_resource_path="./");

        // TODO:
        // Remove doWriteTopic.

        void PublishOperationalDescription();

        void PublishConfiguration();

        void RunSimulation(bool doWriteTopic);

        void HaltSimulation(bool doWriteTopic);

        void ResetSimulation(bool doWriteTopic);

        void SaveSimulation(bool doWriteTopic);

        void Shutdown();

        // Sim properties
        void SetSampleRate(int rate);

        bool IsRunning();

        int GetSampleRate();

        int GetTickCount();

        void TickLoop();

        void onNewSimulationControl(AMM::SimulationControl &simControl, SampleInfo_t *info);

    protected:
        std::thread m_thread;
        std::mutex m_mutex;
        bool m_runThread = false;

        AMM::UUID m_uuid;

        std::string moduleName = "AMM_SimulationManager";
        
        std::string m_DDS_Configuration = "";
        std::string m_DDS_Capabilities  = "";
        
        DDSManager<SimulationManager> *m_mgr = nullptr;

        int m_tickCount = 0;
        int m_sampleRate = 50;

    };

} // namespace AMM
