#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS

string Format::ElapsedTime(long seconds) { 
    string time_str;
    long SS, MM, HH;
    SS = seconds % 60;
    MM = seconds / 60;
    HH = MM / 60;
    MM = MM % 60;
    time_str = std::to_string(HH) + ":" +
                std::to_string(MM) + ":"+
                std::to_string(SS);
    return time_str; 
}