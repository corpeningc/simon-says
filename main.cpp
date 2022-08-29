//  Created by Caleb Corpening

#include "mbed.h"
#include <iostream>
#include <vector>
#include <time.h>

DigitalOut BlueLED(LED3);

DigitalOut GreenLED(LED2);

DigitalOut YellowLED(PTB2);

DigitalOut RedLED(LED1);


AnalogIn BLUE_BUTTON(PTB3);

AnalogIn GREEN_BUTTON(PTB2);

AnalogIn YELLOW_BUTTON(PTB1);

AnalogIn RED_BUTTON(PTB0);

PwmOut Speaker(PTE20);

int getInput();
void intro();
void outro();


float redio_freq = 1.0/200.0;
float yellow_freq = 1.0/300.0;
float green_freq = 1.0/400.0;
float blue_freq = 1.0/500.0;

int main (void) {
  srand(time(0));
  //int q;
  intro();
  while (true) {
    std::vector <int>actual;
    int counter = 0;
    double timer = 1.3;
    BlueLED = 1;
    GreenLED = 1;
    RedLED = 1;
    while (true) {
      int rand_val = rand() % 4;
      std::cout << "Actual : " << rand_val << std::endl;
      actual.push_back(rand_val);
      wait(1);
      for (int i = 0; i < actual.size(); i++) {
          if (actual[i] == 0) {
              BlueLED = 0;
              Speaker.period(blue_freq);
              Speaker = 0.03;
              wait(timer);
              BlueLED = 1;
              Speaker = 0.0;
          }
          else if (actual[i] == 1) {
              GreenLED = 0;
              Speaker.period(green_freq);
              Speaker = 0.03;
              wait(timer);
              GreenLED = 1;
              Speaker = 0.0;
          }
          else if (actual[i] == 2) {
              RedLED = 0;
              GreenLED = 0;
              Speaker.period(yellow_freq);
              Speaker = 0.03;
              wait(timer);
              RedLED = 1;
              GreenLED = 1;
              Speaker = 0.0;
          }
          else if (actual[i] == 3) {
              RedLED = 0;
              Speaker.period(red_freq);
              Speaker = 0.03;
              wait(timer);
              RedLED = 1;
              Speaker = 0.0;
          }
          RedLED = 1;
          GreenLED = 1;
          BlueLED = 1;
          wait(0.2);
      }
      int user_count = 0;
      while (user_count < actual.size()) {
          std::cout << "Waiting for input" << std::endl;
          std::cout << "Red voltage: " << RED_BUTTON.read() << std::endl;
          std::cout << "Blue voltage: " << BLUE_BUTTON.read() << std::endl;
          std::cout << "Green voltage: " << GREEN_BUTTON.read() << std::endl;
          std::cout << "Yellow voltage: " << YELLOW_BUTTON.read() << std::endl;

          int user_choice = getInput();
          std::cout << user_choice << std::endl;
          //std::cout << "CHOICE : " << user_choice << std::endl;
          //std::cout << "VECTOR : " << actual[user_count] << std::endl;
          Speaker = 0.0;
          RedLED = 1;
          BlueLED =1;
          GreenLED = 1;
          if (user_choice == actual[user_count]) {
              user_count++;
          } else {
              user_count = 99;
              break;
          }
          wait(0.5);
      }
      timer = timer * 0.8;
      if (user_count >= 99) {
          std::cout << "LOSER" << std::endl;
          GreenLED = 0;
          RedLED = 0;
          BlueLED=0;
          wait(1);
          GreenLED = 1;
          RedLED = 1;
          BlueLED = 1;
          outro();
          break;
      }
      std::cout << "Score: " << counter << std::endl;
      counter++;
    } // end of round
  } // end of game

}
int getInput() {

    while (true) {
        if( BLUE_BUTTON.read() == 1) {
                BlueLED = 0;
                Speaker.period(blue_freq);
                Speaker = 0.03;
                wait(0.5);
                return 0;
        } 
        if( GREEN_BUTTON.read() == 1) {
                GreenLED = 0;
                Speaker.period(green_freq);
                Speaker = 0.03;
                wait(0.5);
                return 1;
        } 
        if( YELLOW_BUTTON.read() == 1) {
                RedLED = 0;
                GreenLED = 0;
                Speaker.period(yellow_freq);
                Speaker = 0.03;
                wait(0.5);
                return 2;
        }
        if( RED_BUTTON.read() == 1) {
                RedLED = 0;
                Speaker.period(red_freq);
                Speaker = 0.03;
                wait(0.5);
                return 3;
        }
    }
}

void intro() {
  Speaker.period(1.0/2489.0);
  Speaker = 0.03;
  wait(.375);
  Speaker.period(1.0/1244.0);
  wait(.125);
  Speaker.period(1/1864.0);
  wait(.33);
  Speaker.period(1.0/1661.0);
  wait(.57);
  Speaker.period(1.0/2489.0);
  wait(.33);
  Speaker.period(1.0/1864.0);
  wait(1);
  Speaker = 0.0;
  wait(2);
}

void outro() {
 Speaker.period(1.0/1661.0);
 Speaker = 0.03;
 wait(.33);
 Speaker.period(1.0/1244.0);
 wait(.33);
 Speaker.period(1/830.0);
 wait(.33);
 Speaker.period(1.0/952.0);
 wait(.5);
 Speaker = 0.0;
 wait(2);
}
