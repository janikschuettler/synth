//
//  main.cpp
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#include <iostream>
#include "Synth/synth.h"

int main(int argc, const char * argv[]) {
  // insert code here...
  std::cout << "Hello, World!\n";
  
  Synth synth;
  WaveGenerator wv;

  for (int i = 0; i < 100; i++) {
    std::cout << wv.tick() << std::endl;
  }
  
  return 0;
}
