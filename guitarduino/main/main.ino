#include "Timer.h"
#include "TickFuncs.h"

int globalPeriod = 5;

typedef struct task {
  int (*func)(int);  //function pointer
  int period;         //task period
  int elapsedTime;    //time since last tick
  int state = 0;          //current state
} task;

const int num_tasks = 4;
task tasks[num_tasks];

void setup() {
  Serial.begin(9600); //start serial comms
  TimerSet(globalPeriod); //set timer period
  TimerOn();

  for (auto x : display_pins)
      pinMode(x, OUTPUT);
  
  for (auto x : other_output_pins)
      pinMode(x, OUTPUT);

  for (auto x : LED_ROWS)
      digitalWrite(x, LOW);
  
  for (auto x : LED_COLS)
      digitalWrite(x, HIGH);
  //initialize first task
  tasks[0].func = &Test;
  tasks[0].period = 1000;
  tasks[0].elapsedTime = tasks[0].period;

  tasks[1].func = &Tick_SVNSEG;
  tasks[1].period = 5;
  tasks[1].elapsedTime = tasks[1].period;

  tasks[2].func = &Tick_BUZZER;
  tasks[2].period = 150;
  tasks[2].elapsedTime = tasks[2].period;
  
  tasks[3].func = &Tick_LED_MATRIX;
  tasks[3].period = 500;
  tasks[3].elapsedTime = tasks[3].period;

}

void loop() {

  for (int i = 1; i < num_tasks; i++) { //round-robin task execution
    if (tasks[i].elapsedTime >= tasks[i].period) {
      tasks[i].state = tasks[i].func(tasks[i].state);
      tasks[i].elapsedTime = 0;
    }
    tasks[i].elapsedTime += globalPeriod;
  }

  while (!TimerFlag) {} //wait for timer period
  TimerFlag = 0;
}
