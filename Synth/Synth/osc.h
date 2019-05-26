//#include <iostream>
#include <cmath>
#include <limits>
#include <stdint.h>

#define SINE        1
#define SAW         2
#define SQUARE      3
#define TRIANGLE    4


class WaveGenerator
{

  long int phase;

public:
  WaveGenerator();
  ~WaveGenerator();

  int   waveform;
  float frequency;

  float tick();
};


class Oscillator
{

  WaveGenerator voices[5];
  float midiPhaseIncrement[128];
  float sampleRate;

  int   nVoices;
  int   waveform;
  int   pitch;
  int   detuneCoarse;
  float detuneFine;
  float volume;

public:
  Oscillator();
  ~Oscillator();

  float tick();

  void handleNoteOn(uint8_t pitch, uint8_t velocity);
  void handleNoteOff(uint8_t pitch, uint8_t velocity);

  void  setNVoices(int nVoices_);
  int   getNVoices();
  void  setWaveform(int waveform_);
  int   getWaveform();
  void  setPitch(int pitch_);
  int   getPitch();
  void  setDetuneCoarse(int detuneCoarse_);
  int   getDetuneCoarse();
  void  setDetuneFine(float detuneFine_);
  float getDetuneFine();
  void  setVolume(float volume_);
  float getVolume();
};
