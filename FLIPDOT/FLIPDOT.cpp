// - - - - -
// FLIPDOT - A Arduino library for controlling an Annex/AEG flip dot display
// FLIPDOT.cpp: Library implementation file
//
// Copyright (C) 2016 fluepke, kryptokommunist <fabian.luepke@student.hpi.de>,<marcus.ding@student.hpi.de>
// This work is licensed under a GNU style license.
//
// Last change: kryptokommunist
//
// Documentation and samples are available at https://github.com/HPIMakerKlub/Fluepdot
// - - - - -

/* ----- LIBRARIES ----- */
#include "FLIPDOT.h"

/*
Initialize to set the pin mapping as described above
*/
FLIPDOT::FLIPDOT(int pin_mapping[N_PINS]) {

  for(int i = 0; i < N_PINS; i++){
    mapping[i] = pin_mapping[i];
  }


}

/*
Render a frame on the board
*/
void FLIPDOT::render_frame(int16_t frame[ROW_WIDTH]) {

  this->board_init(); //always init board before setting any signals!

  for (int i = 0; i < ROW_WIDTH; i++) {
    if(this->col_changed(i, frame)) {
      this->render_col(frame[i]);
    } else {
      this->skip_col();
    }

  }

}

/*
Prepare the board for sequentially setting the columns
*/
void FLIPDOT::board_init() {

  for(int i = 0; i < N_PINS; i++){
    pinMode(mapping[i], OUTPUT);
  }

  //Init configuration
  digitalWrite(mapping[CLEAR], LOW); //Output a LOW
  this->write_col(COL_ALL_CLEAR); // Pixels are LOW
  digitalWrite(mapping[CLOCK], HIGH); //Output a LOW
  digitalWrite(mapping[RESET], HIGH); //Output a LOW
  delay(30);
  digitalWrite(mapping[RESET], LOW); //Output a HIGH
  digitalWrite(mapping[SELECT], HIGH); //Output a LOW

  delay(30);
  delayMicroseconds(20);

  digitalWrite(mapping[CLEAR], HIGH);
  this->write_col(COL_ALL_SET); // Pixels are HIGH
  delayMicroseconds(200);
  this->write_col(COL_ALL_CLEAR); // Pixels are LOW
  digitalWrite(mapping[CLEAR], LOW);

  delayMicroseconds(200);

  digitalWrite(RESET, HIGH);
  delayMicroseconds(5);
  digitalWrite(SELECT, LOW);
  delayMicroseconds(200);

  //pulse Clock
  digitalWrite(mapping[CLEAR], HIGH);
  this->pulse_clock();
  digitalWrite(mapping[SELECT], HIGH);
  delayMicroseconds(20);
  digitalWrite(mapping[CLEAR], LOW);

}

/*
Render a column on the board, each call will render on the next column on the selected board
*/
void FLIPDOT::render_col(int16_t col) {

  digitalWrite(mapping[CLEAR], HIGH); // Output a high
  delayMicroseconds(200);

  //pulse Clock
  this->pulse_clock();

  // set or clear? that is the question
  this->write_col(col);

  delay(2);

  // turn off all pixel data
  this->write_col(COL_ALL_CLEAR);
  digitalWrite(mapping[CLEAR], LOW);

  delayMicroseconds(200);

  //pulse Clock
  digitalWrite(mapping[CLEAR], HIGH);
  this->pulse_clock();
  delayMicroseconds(20);
  digitalWrite(mapping[CLEAR], LOW);

  delay(2);

}

/*
Toggle clock once
*/
void FLIPDOT::pulse_clock() {

  digitalWrite(mapping[CLOCK], LOW); //Output a HIGH
  delayMicroseconds(20);
  digitalWrite(mapping[CLOCK], HIGH); //Output a low

}

/*
Set the Y-Channels for the currently active row
*/
void FLIPDOT::write_col(int16_t col) {

  for(int i = 0; i < COL_HEIGHT; i++){
    digitalWrite(mapping[i],(col >> i) & 1);
  }

}

bool FLIPDOT::col_changed(int i, int16_t frame[ROW_WIDTH]) {

  //check if any pixel has to be flipped
  return frame_buff[i] ^ frame[i];

}

/*
Skips one column in currently active board. This saves us some time for faster rendering.
*/
void FLIPDOT::skip_col() {

  digitalWrite(mapping[CLEAR], HIGH);
  this->pulse_clock();
  this->pulse_clock();

}
