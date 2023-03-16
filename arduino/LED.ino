/* Facial Emotion Recognition using Hardware */

#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"

#define ROW 1
#define COLUMN 1
#define FONT SystemFont5x7

DMD dmd(ROW, COLUMN);

short matrix[5][56][2] = {
  // angry
  {{9,4},{9,5},{9,6},{9,7},{9,8},{9,9},{9,10},{9,11},{10,3},{10,12},{11,2},{11,13},{12,1},{12,3},{12,6},{12,11},{12,14},{13,1},{13,4},{13,10},{13,14},{14,1},{14,5},{14,9},{14,14},{15,1},{15,9},{15,14},{16,1},{16,9},{16,14},{17,1},{17,5},{17,9},{17,14},{18,1},{18,4},{18,10},{18,14},{19,1},{19,3},{19,6},{19,11},{19,14},{20,2},{20,13},{21,3},{21,12},{22,4},{22,5},{22,6},{22,7},{22,8},{22,9},{22,10},{22,11},},
  // happy
  {{9,4},{9,5},{9,6},{9,7},{9,8},{9,9},{9,10},{9,11},{10,3},{10,12},{11,2},{11,13},{12,1},{12,9},{12,14},{13,1},{13,5},{13,10},{13,14},{14,1},{14,11},{14,14},{15,1},{15,11},{15,14},{16,1},{16,11},{16,14},{17,1},{17,11},{17,14},{18,1},{18,5},{18,10},{18,14},{19,1},{19,9},{19,14},{20,2},{20,13},{21,3},{21,12},{22,4},{22,5},{22,6},{22,7},{22,8},{22,9},{22,10},{22,11},{9,4},{9,4},{9,4},{9,4},{9,4},{9,4},},
  // neutral
  {{9,4},{9,5},{9,6},{9,7},{9,8},{9,9},{9,10},{9,11},{10,3},{10,12},{11,2},{11,13},{12,1},{12,10},{12,14},{13,1},{13,5},{13,10},{13,14},{14,1},{14,10},{14,14},{15,1},{15,10},{15,14},{16,1},{16,10},{16,14},{17,1},{17,10},{17,14},{18,1},{18,5},{18,10},{18,14},{19,1},{19,10},{19,14},{20,2},{20,13},{21,3},{21,12},{22,4},{22,5},{22,6},{22,7},{22,8},{22,9},{22,10},{22,11},{9,4},{9,4},{9,4},{9,4},{9,4},{9,4},},
  // sad
  {{9,4},{9,5},{9,6},{9,7},{9,8},{9,9},{9,10},{9,11},{10,3},{10,12},{11,2},{11,13},{12,1},{12,11},{12,14},{13,1},{13,5},{13,10},{13,14},{14,1},{14,9},{14,14},{15,1},{15,9},{15,14},{16,1},{16,9},{16,14},{17,1},{17,9},{17,14},{18,1},{18,5},{18,10},{18,14},{19,1},{19,11},{19,14},{20,2},{20,13},{21,3},{21,12},{22,4},{22,5},{22,6},{22,7},{22,8},{22,9},{22,10},{22,11},{9,4},{9,4},{9,4},{9,4},{9,4},{9,4},},
  // surprise
  {{9,4},{9,5},{9,6},{9,7},{9,8},{9,9},{9,10},{9,11},{10,3},{10,12},{11,2},{11,13},{12,1},{12,14},{13,1},{13,5},{13,10},{13,11},{13,14},{14,1},{14,9},{14,12},{14,14},{15,1},{15,8},{15,12},{15,14},{16,1},{16,8},{16,12},{16,14},{17,1},{17,9},{17,12},{17,14},{18,1},{18,5},{18,10},{18,11},{18,14},{19,1},{19,14},{20,2},{20,13},{21,3},{21,12},{22,4},{22,5},{22,6},{22,7},{22,8},{22,9},{22,10},{22,11},{9,4},{9,4}},
};

boolean flag = false;

void ScanDMD() {
  dmd.scanDisplayBySPI();
}

void setup() {
  Timer1.initialize(4000);
  Timer1.pwm(PIN_DMD_nOE, 20);
  Timer1.attachInterrupt(ScanDMD);
  
  dmd.clearScreen(1);
  
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    if (!flag) {
      dmd.selectFont(FONT);
      dmd.drawMarquee("Facial Emotion Recognition System - CSMIR, NITD", 47, (32 * ROW) - 1 , 4);
      
      long start = millis();
      long timer = start;
      long timer2 = start;
      boolean ret=false;
      while(!ret){
        if (timer + 40 < millis()) {
          ret = dmd.stepMarquee(-1, 0);
          timer = millis();
        }
      }

      flag = true;
    }
    
    short pos = Serial.read() - '0';
    Serial.println("Value of pos");
    Serial.println(pos);

    if (pos >= 0 && pos < 5) {
      dmd.clearScreen(1);
      for (short i = 0; i < 56; ++i) {
        dmd.writePixel(matrix[pos][i][0], matrix[pos][i][1], GRAPHICS_NORMAL, 1);
      }
    } else {
      dmd.clearScreen(1);
    }
  }
}
