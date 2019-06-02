//
//  synth.h
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#ifndef synth_hpp
#define synth_hpp

#include <stdint.h>

#define SAMPLE_RATE 44100.0

#include "audio.h"
#include "osc.h"
#include "mixr.h"

#endif /* synth_hpp */

//class Synth
//{
//  Oscillator oscs[2];
//
//public:
//  Synth();
//  ~Synth();
//
//  float sampleRate;
//  long int output;
//
//  void tick();
//
//  void handleNoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity);
//  void handleNoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity);
//};
