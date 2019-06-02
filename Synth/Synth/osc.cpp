//
//  osc.cpp
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#include "osc.h"

WaveGenerator::WaveGenerator() {
  WaveGenerator(440.0, SAW);
}

WaveGenerator::WaveGenerator(float frequency, int waveform) {
  phase_     = 0;
  waveform_  = waveform;
  frequency_ = frequency;
}

void WaveGenerator::tick()
{
  float amplitude = 0.0;
  float int_max = (float) std::numeric_limits<long int>::max();
  float tick = phase_ / int_max;

  switch(waveform_) {
    case SINE:
      amplitude = sin(2 * M_PI * tick);
      break;
    case SAW:
      amplitude = tick;
      break;
    case SQUARE:
      if (tick >= 0.0) {
        amplitude = 1.0;
      } else {
        amplitude = -1.0; //0.0
      }
      break;
    case TRIANGLE:
      if (tick >= 0.0) {
        amplitude = 2 * tick - 1;
      } else {
        amplitude = 2 * -tick - 1;
      }
      break;
    case NOISE:
      amplitude = (audio) 2.0 * std::rand() / RAND_MAX - 1.0;
      break;
    default: 
      break;
  }
  
  float sampleRate = 44100.0;
  float ticksPerCycle = int_max / sampleRate;
  
  phase_ += (long int)frequency_ * ticksPerCycle;

  value_ = amplitude;
}

audio WaveGenerator::output() {
  return value_;
}

void WaveGenerator::waveform(int waveform) {
  waveform_ = waveform;
}
int  WaveGenerator::waveform() {
  return waveform_;
}
void  WaveGenerator::frequency(float frequency) {
  frequency_ = frequency;
}
float WaveGenerator::frequency() {
  return frequency_;
}


Oscillator::Oscillator() {
  nVoices_      = 1;
  waveform_     = SAW;
  pitch_        = 0;
  detune_       = 0.0;
  
  oscMixr       = Mixr(nVoices_);

  sampleRate_   = 44100.0;

  float ticksPerCycle = std::numeric_limits<long int>::max() / sampleRate_;

  for(int n = 0; n < 128; n++) {
    // Correct calculation for frequency
    float frequency = ((pow(2.0,(n-69.0)/12.0)) * 440.0);
    midiPhaseIncrement_[n] = frequency*ticksPerCycle;
  }
}

void  Oscillator::nVoices(int nVoices) { nVoices_ = nVoices; }
int   Oscillator::nVoices() { return nVoices_; }
void  Oscillator::waveform(int waveform) {
  waveform_ = waveform;
  for (std::pair<int, voiceWrapper> voice : voices_) {
    voice.second.oscillator.waveform(waveform);
  }
}
int   Oscillator::waveform() { return waveform_; }
void  Oscillator::pitch(int pitch) { pitch_ = pitch; }
int   Oscillator::pitch() { return pitch_; }
void  Oscillator::detune(float detune) { detune_ = detune; }
float Oscillator::detune() { return detune_; }


void Oscillator::tick() {
  value_ = 0.0;
  for (std::pair<int, voiceWrapper> voice : voices_) {
    WaveGenerator *oscillator = &voice.second.oscillator;
    oscillator->tick();
//    voice.second.oscillator.tick();
    // temp implementation
    audio shiftedOutput = (oscillator->output() + 1.0) / 2.0;
    value_ += shiftedOutput;
  }
}

audio Oscillator::output() {
  return value_;
}

void Oscillator::handleNoteOn(uint8_t pitch, uint8_t velocity) {
  float frequency = midiPhaseIncrement_[pitch];
  WaveGenerator newWaveGenerator(frequency, waveform_);
  voiceWrapper newVoice {pitch, velocity, newWaveGenerator};
  
  voices_[keyId(pitch, velocity)] = newVoice;
}

void Oscillator::handleNoteOff(uint8_t pitch, uint8_t velocity) {
  voices_.erase(keyId(pitch, velocity));
}

int Oscillator::keyId(uint8_t pitch, uint8_t velocity) {
  return pitch * 1000 + velocity;
}
