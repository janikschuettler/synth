#include "osc.h"

WaveGenerator::WaveGenerator() {
  waveform  = SINE;
  frequency = 440.0;
}

WaveGenerator::~WaveGenerator() {
  
}

float WaveGenerator::tick() 
{
  float amplitude = 0.0;
  float int_max = (float) std::numeric_limits<long int>::max();
  float tick = phase / int_max;

  switch(waveform) {
    case SINE:
      amplitude = 0.5 * (1 + sin(2 * M_PI * tick));
      break;
    case SAW:
      amplitude = tick;
      break;
    case SQUARE:
      if (tick >= 0.5) {
        amplitude = 1.0;
      } else {
        amplitude = 0.0;
      }
      break;
    case TRIANGLE:
      if (tick >= 0.5) {
        amplitude = 2 * tick;
      } else {
        amplitude = 2 * (1 - tick);
      }
      break;
    default: 
      break;
  }
  
  float sampleRate = 44100.0;
  float ticksPerCycle = int_max / sampleRate;
  
  phase += (long int)frequency * ticksPerCycle;

  return amplitude;
}


Oscillator::Oscillator() {
  nVoices      = 5;
  waveform     = SAW;
  pitch        = 0;
  detuneCoarse = 0;
  detuneFine   = 0.0;
  volume       = 1.0;

  sampleRate   = 44100.0;

  float ticksPerCycle = std::numeric_limits<long int>::max() / sampleRate;

  for(int n = 0; n < 128; n++) {
    // Correct calculation for frequency
    float frequency = ((pow(2.0,(n-69.0)/12.0)) * 440.0);
    midiPhaseIncrement[n] = frequency*ticksPerCycle;
  }

  for(int n = 0; n < nVoices; n++) {
    WaveGenerator newGenerator;
    voices[n] = newGenerator;
  }
}

Oscillator::~Oscillator() {
  
}

float Oscillator::tick() {
  for(int n = 0; n < nVoices; n++) {
    WaveGenerator newGenerator;
    voices[n].tick();
  }
  
  return 0.0;
}

void Oscillator::handleNoteOn(uint8_t pitch, uint8_t velocity) {

}

void Oscillator::handleNoteOff(uint8_t pitch, uint8_t velocity) {

}

void  Oscillator::setNVoices(int nVoices_) { nVoices = nVoices_; }
int   Oscillator::getNVoices() { return nVoices; }
void  Oscillator::setWaveform(int waveform_) { waveform = waveform_; }
int   Oscillator::getWaveform() { return waveform; }
void  Oscillator::setPitch(int pitch_) { pitch = pitch_; }
int   Oscillator::getPitch() { return pitch; }
void  Oscillator::setDetuneCoarse(int detuneCoarse_) { detuneCoarse = detuneCoarse_; }
int   Oscillator::getDetuneCoarse() { return detuneCoarse; }
void  Oscillator::setDetuneFine(float detuneFine_) { detuneFine = detuneFine_; }
float Oscillator::getDetuneFine() { return detuneFine; }
void  Oscillator::setVolume(float volume_) { volume = volume_; }
float Oscillator::getVolume() { return volume; }
