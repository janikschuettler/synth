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

void MixrChannel::input(AudioModule &input) {
  std::cout << "id input this " << this << std::endl;
  std::cout << "id input " << &input << std::endl;
  input_ = &input;
}
AudioModule* MixrChannel::input() { return input_; }
void  MixrChannel::volume(float volume) { volume_ = volume; }
float MixrChannel::volume() { return volume_; }

audio MixrChannel::output() {
  return volume_ * input_->output();
}



Mixr::Mixr() {
}

audio Mixr::output() {
  audio output  = 0.0;
  float volumes = 0.0;
  
  for (std::pair<int, MixrChannel*> channel : channels_) {
    output  += channel.second->output();
    volumes += channel.second->volume();
  }
  
  output /= volumes;
  
  return output;
}

MixrChannel* Mixr::addChannel(int channelId) {
  MixrChannel newMixrChannel;
  channels_[channelId] = &newMixrChannel;
  
  std::cout << "Mixr: adding new channel with location " << &newMixrChannel << std::endl;
  std::cout << "Mixr: adding new channel with location " << channels_[channelId] << std::endl;
  
  return Mixr::channel(channelId);
}

void Mixr::deleteChannel(int channelId) {
  channels_.erase(channelId);
}

MixrChannel* Mixr::channel(int channelId) {
  return channels_[channelId];
}
