//
//  mixr.h
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#ifndef mixr_hpp
#define mixr_hpp

#include <iostream>
#include "audio.h"

class MixrChannel : public AudioModule {
  float volume_;
  AudioModule* input_;
  
public:
  MixrChannel();
  
  void input(AudioModule &input);
  AudioModule* input();
  void  volume(float volume);
  float volume();
  
  audio output() override;
};

class Mixr : public AudioModule
{
  int nChannels_ = 5;
  MixrChannel* channels_;
  
public:
  Mixr();
  Mixr(int nChannels);
  
  int  nChannels();
  void nChannels(int nChannels);
  
  audio output();
  MixrChannel* channel(int channelIndex);
};

#endif /* mixr_hpp */
