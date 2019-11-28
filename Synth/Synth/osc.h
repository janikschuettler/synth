//
//  osc.h
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#ifndef osc_hpp
#define osc_hpp

#include <cmath>
#include <limits>
#include <map>
#include <stdint.h>

#include "audio.h"
#include "mixr.h"


#define SINE        1
#define SAW         2
#define SQUARE      3
#define TRIANGLE    4
#define NOISE       5

typedef long int tick_counter;

#define TICK_MAX  (float) std::numeric_limits<tick_counter>::max();


class WaveGenerator : public AudioModule
{
  audio value_;
  tick_counter phase_;
  
  int   waveform_;
  float frequency_;

public:
  WaveGenerator();
  WaveGenerator(float frequency, int waveform);

  void tick();
  audio output();
  
  void waveform(int waveform);
  int  waveform();
  void  frequency(float frequency);
  float frequency();
};

struct voiceWrapper {
  uint8_t pitch;
  uint8_t velocity;
  WaveGenerator* oscillator;
};


class Oscillator : public AudioModule
{

  voiceWrapper voices2_[1];
  std::map<int, voiceWrapper*> voices_;
  float midiPhaseIncrement_[128];
  float sampleRate_;
  
  Mixr oscMixr;
  
  float value_;

  int   nVoices_;
  int   waveform_;
  int   pitch_;
  float detune_;
  
  int keyId(uint8_t pitch, uint8_t velocity);

public:
  Oscillator();
  
  // getters and setters
  void  nVoices(int nVoices);
  int   nVoices();
  void  waveform(int waveform);
  int   waveform();
  void  pitch(int pitch);
  int   pitch();
  void  detune(float detune);
  float detune();

  void tick();
  audio output();

  void handleNoteOn(uint8_t pitch, uint8_t velocity);
  void handleNoteOff(uint8_t pitch, uint8_t velocity);
};


#endif /* osc_hpp */
