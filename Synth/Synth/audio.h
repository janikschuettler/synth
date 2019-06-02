//
//  audio.h
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#ifndef audio_hpp
#define audio_hpp

typedef float audio;

class AudioModule {
public:
  virtual audio output() {
    return 0.5;
  };
  void input(AudioModule input);
};

#endif /* audio_hpp */
