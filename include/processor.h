#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
 Processor(){
     prevIdleTime_ = 0;
     prevTotalTime_ = 0;
 }
  float Utilization();  // TODO: See src/processor.cpp
  long PrevTotalTime(){ return prevTotalTime_;}
  long PrevIdleTime(){return prevIdleTime_;}
  void PrevTotalTime(long t){prevTotalTime_ = t;}
  void PrevIdleTime(long t){prevIdleTime_ = t;}
 
  // TODO: Declare any necessary private members
 private:
 long prevTotalTime_;
 long prevIdleTime_;

 };

#endif