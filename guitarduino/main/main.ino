#include "Timer.h"
#include "TickFuncs.h"

int globalPeriod = 10;

typedef struct task {
  int (*func)(void);  //function pointer
  int period;         //task period
  int elapsedTime;    //time since last tick
} task;

const int num_tasks = 1;
task tasks[num_tasks];

void setup() {
  Serial.begin(9600); //start serial comms
  TimerSet(globalPeriod); //set timer period
  TimerOn();

  for (auto x : display_pins)
      pinMode(x, OUTPUT);

  //initialize first task
  tasks[0].func = &Test;
  tasks[0].period = 1000;
  tasks[0].elapsedTime = tasks[0].period;

  tasks[1].func = &Tick_SVNSEG;
  tasks[1].period = 10;
  tasks[1].elapsedTime = tasks[1].period;
}

void loop() {

  for (int i = 0; i < num_tasks; i++) { //round-robin task execution
    if (tasks[i].elapsedTime >= tasks[i].period) {
      tasks[i].func();
      tasks[i].elapsedTime = 0;
    }
    tasks[i].elapsedTime += globalPeriod;
  }

  while (!TimerFlag) {} //wait for timer period
  TimerFlag = 0;
}
