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

int main(int argc, const char * argv[]) {
  
//  C device1;
//
////  MixrChannel device2;
//////  device2.setDevice(device1);
////  device2.input(device1);
////  std::cout << device2.output() << std::endl;
//
//  Mixr device2(2);
//  device2.channel(0)->input(device1);
////  device2.device_ = &device1;
//  std::cout << device2.channel(0)->output() << std::endl;
  

  Oscillator osc0;
  Oscillator osc1;
  Mixr mixr(2);

  osc0.waveform(SINE);
  osc0.pitch(-12);

  osc1.waveform(SAW);

  mixr.channel(0)->input(osc0);
  mixr.channel(1)->input(osc1);

  mixr.channel(0)->volume(1);
  mixr.channel(1)->volume(0.5);
  
  std::cout << "rand = " << std::rand() << ", max " << (float) std::rand() / RAND_MAX << std::endl;
  
  osc0.handleNoteOn(69, 127);
  osc1.handleNoteOn(40, 127);

  int n = 4000;
  std::vector<double> t(n), a(n), b(n), c(n);
  for(int i = 0; i < n; ++i) {
    osc0.tick();
    osc1.tick();
    t.at(i) = i; //i*i;
    a.at(i) = osc0.output(); //sin(2*M_PI*i/360.0);
    b.at(i) = osc1.output(); //sin(2*M_PI*i/360.0);
    c.at(i) = mixr.output(); //(osc0.output() + osc1.output()) / 2; //sin(2*M_PI*i/360.0);

    std::cout << mixr.output() << " and " << osc0.output() << std::endl;
  }

  matplotlibcpp::figure_size(1200, 780);
  matplotlibcpp::plot(t,a);
  matplotlibcpp::plot(t,b);
  matplotlibcpp::plot(t,c);
//  matplotlibcpp::ylim(-1.1, 1.1);
  matplotlibcpp::save("./out.png");

  return 0;
}
