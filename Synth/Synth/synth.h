#include "osc.h"
#include <stdint.h>

class Synth
{
  Oscillator oscs[2];

public:
  Synth();
  ~Synth();

  float sampleRate;
  long int output;

  void tick();

  void handleNoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity);
  void handleNoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity);
};
