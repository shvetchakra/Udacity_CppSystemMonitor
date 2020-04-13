#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include "process.h"

#include <vector>

using std::vector;
int main() {
  System system;
  Processor P;
  system.Cpu(P);
  vector<int> pids = LinuxParser::Pids();
  vector<Process> processes ;
  for(auto it = pids.begin(); it!=pids.end();++it)
  {
    Process P;
    P.Pid(*it);
    processes.push_back(P);
  }
  system.Processes(processes);
  NCursesDisplay::Display(system);
}