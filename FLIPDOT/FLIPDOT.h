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

#include <inttypes.h>
#include <Arduino.h>


#ifndef FLIPDOT_h
#define FLIPDOT_h

// ---- Constants ----

#define COL_HEIGHT 16
#define ROW_WIDTH 25
#define N_PINS 20 // we have 20 pins to control 17Y-Channel + 1Clear + 1Select + 1Clock + 1Reset = 20
#define CLEAR 16 // see below
#define SELECT 17 // see below
#define CLOCK 18 // see below
#define RESET 19 // see below
#define COL_ALL_CLEAR 0b0000000000000000
#define COL_ALL_SET 0b1111111111111111

// ---- Methods ----

class FLIPDOT {

//FLIPDOT PIN Mapping # <-- 16 Y-Channels --><-- 1 Clear --><-- 1 Select --><-- 1 Clock --><-- 1 Reset -->
//pos                           0 - 15                16              17            18            19
int mapping[N_PINS] = {};

//frame buffer (for super fancy diffing etc.)
int16_t frame_buff[ROW_WIDTH];

public:
  FLIPDOT(int pin_mapping[N_PINS]);
  void render_frame(int16_t col[ROW_WIDTH]);

private:
  void FLIPDOT::pulse_clock();
  void board_init();
  void render_col(int16_t col);
  void write_col(int16_t col);
  void skip_col();
  bool col_changed(int i, int16_t frame[ROW_WIDTH]);

};

#endif
