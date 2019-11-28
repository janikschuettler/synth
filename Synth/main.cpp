//
//  main.cpp
//  Synth
//
//  Created by Janik Schütter on 5/26/19.
//  Copyright © 2019 Janik Schütter. All rights reserved.
//

#include <iostream>
#include <cmath>

#include "matplotlibcpp.h"
#include "Synth/synth.h"
//#include "Synth/osc.h"
//#include "Synth/mixr.h"

class A : public AudioModule {
  audio value_ = 0.0;
  
public:
  audio output() {
    return value_;
  };
  void tick() {
    value_ += 1.0;
  };
};

class B : public AudioModule {
public:
  audio output() {
    return 0.5;
  };
  void tick() {};
};

int main(int argc, const char * argv[]) {
  // create oscillators
//  A osc0;
//  B osc1;
  Oscillator osc0;
//  Oscillator osc1;

  osc0.waveform(SINE);
  osc0.pitch(-12);
//  osc1.waveform(SAW);
  
  // wire everything together
  Mixr mixr;
  mixr.addChannel(0);
  mixr.channel(0)->input(osc0);
//  mixr.addChannel(1);
//  mixr.channel(1)->input(osc1);
//  mixr.channel(1)->volume(1);
  
//  std::cout << "channel_0 " << mixr.channel(0) << ", channel_1 " << mixr.channel(1) << std::endl;
  
  // play a note
//  osc0.handleNoteOn(69, 127);
//  osc1.handleNoteOn(40, 127);
  
  std::cout << "mixr " << &mixr << std::endl;
  std::cout << "channel " << mixr.channel(0) << std::endl;
  std::cout << "osc " << mixr.channel(0)->input() << ", " << &osc0 << std::endl;

  
  int n = 40;
  std::vector<double> t(n), a(n), b(n), c(n);
  for(int i = 0; i < n; ++i) {
    std::cout << " ====== " << i << " ======= " << std::endl;
    osc0.tick();
//    osc1.tick();
    t.at(i) = i; //i*i;
    a.at(i) = osc0.output(); //sin(2*M_PI*i/360.0);
//    b.at(i) = osc1.output(); //sin(2*M_PI*i/360.0);
    c.at(i) = mixr.output(); //(osc0.output() + osc1.output()) / 2; //sin(2*M_PI*i/360.0);

//    std::cout << mixr.output() << " (osc0 = " << osc0.output() << ", osc1 = " << osc1.output() << ")" << std::endl;
  }

  matplotlibcpp::figure_size(1200, 780);
  matplotlibcpp::plot(t,a);
  matplotlibcpp::plot(t,b);
  matplotlibcpp::plot(t,c);
//  matplotlibcpp::ylim(-1.1, 1.1);
  matplotlibcpp::save("./out.png");

  return 0;
}
