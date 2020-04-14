#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    int count = 13;
  string line;
  string utime, stime, cutime, cstime, starttime;
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid_) + LinuxParser::kStatFilename);
  if (stream.is_open()){
  std::getline(stream, line);
  std::istringstream linestream(line);
  while(linestream >> utime){
    if(--count == 0)
      break;
    }
    linestream >> utime >> stime >>cutime >> cstime;
    
  }
    long int processActiveTime = (std::stol(utime) + std::stol(stime) 
                                + std::stol(cutime) +std::stol(cstime));

    long processUpTime = LinuxParser::UpTime(pid_);
    if(processUpTime > 0)
        return float(processActiveTime/processUpTime);
    
    return 0;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    string cmd = LinuxParser::Command(pid_);
    return cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    string ramInKB = LinuxParser::Ram(pid_);
    if (ramInKB != ""){
    long ramKB = std::stol(ramInKB);
    string ramInMB = to_string(ramKB/1024);
    return ramInMB;
    }
    return "";
     }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return this->cpu_ > a.cpu_ ? true : false; }