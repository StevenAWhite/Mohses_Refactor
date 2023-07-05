#pragma once

#include "amm_std.h"

#include "amm/Utility.h"

#include "amm/TopicNames.h"

#include <tinyxml2.h>

#include "thirdparty/sqlite_modern_cpp.h"

namespace AMM {

/// Definition for Logs.
    struct LogEntry {
        std::string source;
        std::string topic;
        std::string event_id;
        uint64_t timestamp;
        std::string data = "";
    };

/// Container for Module Manager logic.
    class ModuleManager : ListenerInterface {

    public:


    private:

    protected:

        /// This module's id.
        AMM::UUID m_uuid;

        /// This module's name.
        std::string moduleName = "AMM_ModuleManager";

        /// This module's path to the config file.
        const std::string config_file = "config/module_manager_amm.xml";

        /// DDS Manager for this module.
        DDSManager <ModuleManager> *m_mgr = new DDSManager<ModuleManager>(config_file);

        std::mutex m_mapmutex;

    public:
        ModuleManager();

        ~ModuleManager();

        void PublishOperationalDescription();

        void PublishConfiguration();

        void Shutdown();

        void ShowStatus();

        void WriteLogEntry(LogEntry log);

        void ParseScenarioFromFile(const std::string xmlFileName);

        void ClearEventLog();

        void ClearDiagnosticLog();

        void SendTestCommand(const std::string action);

        std::string ExtractGUIDToString(GUID_t guid);

        uint64_t GetTimestamp();

    private:
        /// Enables
        void RunSimulation();

        void HaltSimulation();

        void ResetSimulation();

        void SaveSimulation();

        const std::string loadScenarioPrefix = "LOAD_SCENARIO:";
        const std::string loadStatePrefix = "LOAD_STATE:";
        const std::string sysPrefix = "[SYS]";
        const std::string actPrefix = "[ACT]";
        const std::string loadPrefix = "LOAD_STATE:";

        std::string currentScenario = "NONE";
        std::string currentState = "NONE";
        std::string currentStatus = "NOT RUNNING";

        bool isPaused = false;

    protected:

        /// Event listener for Logs.
        void onNewLog(AMM::Log &log, SampleInfo_t *info);

        /// Event listener for Module Configuration
        void onNewModuleConfiguration(AMM::ModuleConfiguration &mc, SampleInfo_t *info);

        /// Event listener for Status
        void onNewStatus(AMM::Status &status, SampleInfo_t *info);

        /// Event listener for Simulation Controller
        void onNewSimulationControl(AMM::SimulationControl &simControl, SampleInfo_t *info);

        /// Event listener for Assessment.
        void onNewAssessment(AMM::Assessment &assessment, SampleInfo_t *info);

        /// Event listener for Event Fragment.
        void onNewEventFragment(AMM::EventFragment &eventFrag, SampleInfo_t *info);

        /// Event listener for Event Record.
        void onNewEventRecord(AMM::EventRecord &eventRec, SampleInfo_t *info);

        /// Event listener for Fragment Amendment Request.
        void onNewFragmentAmendmentRequest(AMM::FragmentAmendmentRequest &ffar, SampleInfo_t *info);

        /// Event listener for Omitted Event.
        void onNewOmittedEvent(AMM::OmittedEvent &omittedEvent, SampleInfo_t *info);

        /// Event listener for Operational Description.
        void onNewOperationalDescription(AMM::OperationalDescription &opDescript, SampleInfo_t *info);

        /// Event listener for Render Modification.
        void onNewRenderModification(AMM::RenderModification &rendMod, SampleInfo_t *info);

        /// Event listener for Physiology Modification.
        void onNewPhysiologyModification(AMM::PhysiologyModification &physMod, SampleInfo_t *info);

        /// Event lsitener for Command.
        void onNewCommand(AMM::Command &command, eprosima::fastrtps::SampleInfo_t *info);

        void ParseCapabilities(tinyxml2::XMLElement *node);

        void ParseMetadata(tinyxml2::XMLElement *node);
    };


} // namespace AMM
