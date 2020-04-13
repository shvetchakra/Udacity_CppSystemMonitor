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
  NCursesDisplay::Display(system);
}