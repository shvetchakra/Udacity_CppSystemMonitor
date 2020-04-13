#include "processor.h"
#include "linux_parser.h"


using std::stol;
using std::string;
using std::to_string;
using std::vector;

using LinuxParser::CPUStates;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> csVector;
    float cpuUtil{0.0};
    csVector = LinuxParser::CpuUtilization();
    long userTime, niceTime, idleAllTime, sysAllTime, virtAllTime, totalTime;
    vector<long> csVectorTrans;
    std::transform(csVector.begin(), csVector.end(), std::back_inserter(csVectorTrans),
               [](const std::string& str) { return stol(str); });
    userTime = csVectorTrans[static_cast<int>(CPUStates::kUser_)] - csVectorTrans[static_cast<int>(CPUStates::kGuest_)];
    niceTime = csVectorTrans[static_cast<int>(CPUStates::kNice_)] - csVectorTrans[static_cast<int>(CPUStates::kGuestNice_)];
    idleAllTime = csVectorTrans[static_cast<int>(CPUStates::kIdle_)] + csVectorTrans[static_cast<int>(CPUStates::kIOwait_)];
    sysAllTime = csVectorTrans[static_cast<int>(CPUStates::kSystem_)] + csVectorTrans[static_cast<int>(CPUStates::kIRQ_)] +
                                                    csVectorTrans[static_cast<int>(CPUStates::kSoftIRQ_)];
    virtAllTime = csVectorTrans[static_cast<int>(CPUStates::kGuestNice_)] + csVectorTrans[static_cast<int>(CPUStates::kGuest_)];
    totalTime = userTime + niceTime + idleAllTime + sysAllTime + virtAllTime + csVectorTrans[static_cast<int>(CPUStates::kSteal_)];

    float deltaTotalTime = totalTime - PrevTotalTime();
    float deltaIdleTime = idleAllTime - PrevIdleTime();

    PrevIdleTime(idleAllTime);
    PrevTotalTime(totalTime);
    LinuxParser::ActiveJiffies( totalTime - idleAllTime );
    LinuxParser::Jiffies( totalTime);
    LinuxParser::IdleJiffies( idleAllTime);
    cpuUtil = (deltaTotalTime - deltaIdleTime)/deltaTotalTime;

    return cpuUtil; 
    }
