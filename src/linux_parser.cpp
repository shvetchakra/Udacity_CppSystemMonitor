#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>


#include "linux_parser.h"
#include "processor.h"
using std::stof;
using std::string;
using std::to_string;
using std::vector;
namespace LinuxParser {
  long jiffies_{0};
  long activeJiffies_{0};
  long idleJiffies_{0};
}
// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float percentage_mem_used = 0.0;
  float total_mem = 1.0;
  float free_mem = 1.0;
  float used_mem = 0.0;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "MemTotal:")
      {
        total_mem = stof(value);
      }
      if(key == "MemFree:")
        {
          free_mem = stof(value);
          break;
        }

    }
  }
  used_mem = total_mem - free_mem;
  percentage_mem_used = (used_mem / total_mem);
  return percentage_mem_used; 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return jiffies_; }
void LinuxParser::Jiffies(long j){ jiffies_ = j;}
// TODO: Read and return the number of active jiffies for a PID

long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
  return 0;
   }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return activeJiffies_; }
void LinuxParser::ActiveJiffies(long j){activeJiffies_ = j;};
// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return idleJiffies_; }
void LinuxParser::IdleJiffies(long j){idleJiffies_ = j;}
// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  
  vector<string> cpuStatesVector;
  string key;
  string value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if(key == "cpu"){
        
        while(linestream >> value)
        {
          cpuStatesVector.push_back(value);
        }
        break;
      }
      else
      {
        continue;
      }
      
    }
  }
  return cpuStatesVector; 

  }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int total_processes;
  string key;
  int value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "processes"){
        total_processes = value;
        break;
      }
      else
      {
        continue;
      }
      
    }
  }
  return total_processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int running_processes;
  string key;
  int value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "procs_running"){
        running_processes = value;
        break;
      }
      else
      {
        continue;
      }
      
    }
  }
  return running_processes;
 }

// TODO: Read and return the command associated with a process

string LinuxParser::Command(int pid) { 
  string cmd;
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
    }
  return string(); }

// TODO: Read and return the memory used by a process

string LinuxParser::Ram(int pid) { 
  
  string ram;
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "VmSize:"){
        ram = value;
        break;
      }
      else
      {
        continue;
      }
      
    }
  }
  return ram;
  }

// TODO: Read and return the user ID associated with a process

string LinuxParser::Uid(int pid) { 
  
  string uid;
  string key, value;
  string line;
 
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "Uid:"){
        uid = value;
        return uid;
        
      }
      else
      {
        continue;
      }
      
    }
  }
  return string(); 
  }

// TODO: Read and return the user associated with a process

string LinuxParser::User(int pid) { 
  string uid = LinuxParser::Uid(pid);
  string line;
  string uname, temp,tempuid;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()){
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> uname >> temp >> tempuid) {
        if(tempuid == uid)
        {
          return uname;
        }
        else
        {
          continue;
        }
     }
    }    
  }
  return string();
  }


// TODO: Read and return the uptime of a process

long LinuxParser::UpTime(int pid) { 
  
  int count = 20;
  string line;
  string utime;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()){
  std::getline(stream, line);
  std::istringstream linestream(line);
  while(linestream >> utime){
    if(count-- == 0)
      break;
    }
    linestream >> utime;
  }
  long int sysUptime = LinuxParser::UpTime();
  long int proUptime = std::stol(utime)/sysconf(_SC_CLK_TCK);
  return (sysUptime - proUptime); 
  }