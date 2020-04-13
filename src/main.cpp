#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  Processor P;
  system.Cpu(P);
  NCursesDisplay::Display(system);
}