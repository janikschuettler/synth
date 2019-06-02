//
//  mixr.cpp
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#include "mixr.h"

MixrChannel::MixrChannel() {
  volume_ = 1.0;
}

void MixrChannel::input(AudioModule &input) { input_ = &input; }
AudioModule* MixrChannel::input() { return input_; }
void  MixrChannel::volume(float volume) { volume_ = volume; }
float MixrChannel::volume() { return volume_; }

audio MixrChannel::output() {
  return volume_ * input_->output();
}



Mixr::Mixr() {
  Mixr(2);
}

Mixr::Mixr(int nChannels) {
  nChannels_ = nChannels;
  channels_  = new MixrChannel[nChannels_];
}

int Mixr::nChannels() { return nChannels_; }
void Mixr::nChannels(int nChannels) { nChannels_ = nChannels; }

audio Mixr::output() {
  audio output  = 0.0;
  float volumes = 0.0;
  
  for (int i = 0; i < nChannels_; i++) {
    output  += channels_[i].output();
    volumes += channels_[i].volume();
  }
  
  output /= volumes;
  
  return output;
}

MixrChannel* Mixr::channel(int channelIndex) {
  return &channels_[channelIndex];
}
