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
#include <map>
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
  std::map<int, MixrChannel*> channels_;
  
public:
  Mixr();
  
  audio output();
  
  MixrChannel* addChannel(int channelId);
  void deleteChannel(int channelId);
  MixrChannel* channel(int channelId);
};

#endif /* mixr_hpp */
