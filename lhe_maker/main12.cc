/// main11.cc is a part of the PYTHIA process generator.
// Copyright (C) 2011 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

#include "Pythia8/Pythia.h"
//#include <fstream>
using namespace Pythia8;
int main() {
    
    Pythia pythia;
    //string namefile[417] ={"-10kt1.5cT-1cg0c2g0.lhe", "-12.5kt1.5cT-1cg0c2g0.lhe", "-12.5kt2.5cT-3cg0c2g0.lhe", "-15kt1.5cT-1cg0c2g0.lhe", "-1kt1cT0cg-0.2c2g0.2.lhe", "-1kt1cT0cg-0.4c2g0.4.lhe", "-1kt1cT0cg-0.6c2g0.6.lhe", "-1kt1cT0cg-0.8c2g0.8.lhe", "-1kt1cT0cg-1c2g1.lhe", "-1kt1cT0cg0.2c2g-0.2.lhe", "-1kt1cT0cg0.4c2g-0.4.lhe", "-1kt1cT0cg0.6c2g-0.6.lhe", "-1kt1cT0cg0.8c2g-0.8.lhe", "-1kt1cT0cg0c2g0.lhe", "-1kt1cT0cg1c2g-1.lhe", "-2.4kt1.5cT-1cg0c2g0.lhe", "-2.4kt1cT0cg-0.2c2g0.2.lhe", "-2.4kt1cT0cg-0.4c2g0.4.lhe", "-2.4kt1cT0cg-0.6c2g0.6.lhe", "-2.4kt1cT0cg-0.8c2g0.8.lhe", "-2.4kt1cT0cg-1c2g1.lhe", "-2.4kt1cT0cg0.2c2g-0.2.lhe", "-2.4kt1cT0cg0.4c2g-0.4.lhe", "-2.4kt1cT0cg0.6c2g-0.6.lhe", "-2.4kt1cT0cg0.8c2g-0.8.lhe", "-2.4kt1cT0cg0c2g0.lhe", "-2.4kt1cT0cg1c2g-1.lhe", "-3.5kt0.5cT-0.5cg0c2g0.lhe", "-3.5kt0.5cT-1cg0c2g0.lhe", "-3.5kt0.5cT-2cg0c2g0.lhe", "-3.5kt0.5cT-3cg0c2g0.lhe", "-3.5kt0.5cT0.5cg0c2g0.lhe", "-3.5kt0.5cT1.5cg0c2g0.lhe", "-3.5kt0.5cT1cg0c2g0.lhe", "-3.5kt0.5cT2.0cg0c2g0.lhe", "-3.5kt0.5cT2.5cg0c2g0.lhe", "-3.5kt0.5cT2cg0c2g0.lhe", "-3.5kt0.5cT3cg0c2g0.lhe", "-3.5kt1.5cT-0.5cg0c2g0.lhe", "-3.5kt1.5cT-1cg0c2g0.lhe", "-3.5kt1.5cT-2cg0c2g0.lhe", "-3.5kt1.5cT-3cg0c2g0.lhe", "-3.5kt1.5cT1cg0c2g0.lhe", "-3.5kt1.5cT2cg0c2g0.lhe", "-3.5kt1.5cT3cg0c2g0.lhe", "-3.5kt1cT0.5cg0c2g0.lhe", "-3.5kt1cT1.5cg0c2g0.lhe", "-3.5kt1cT2.0cg0c2g0.lhe", "-3.5kt1cT2.5cg0c2g0.lhe", "-3.5kt2.0cT-0.5cg0c2g0.lhe", "-3.5kt2.0cT-1cg0c2g0.lhe", "-3.5kt2.0cT-2cg0c2g0.lhe", "-3.5kt2.0cT-3cg0c2g0.lhe", "-3.5kt2.0cT0.5cg0c2g0.lhe", "-3.5kt2.0cT1cg0c2g0.lhe", "-3.5kt2.0cT2cg0c2g0.lhe", "-3.5kt2.0cT3cg0c2g0.lhe", "-3.5kt2.5cT-0.5cg0c2g0.lhe", "-3.5kt2.5cT-1cg0c2g0.lhe", "-3.5kt2.5cT-2cg0c2g0.lhe", "-3.5kt2.5cT-3cg0c2g0.lhe", "-3.5kt2.5cT0.5cg0c2g0.lhe", "-3.5kt2.5cT1cg0c2g0.lhe", "-3.5kt2.5cT2cg0c2g0.lhe", "-3.5kt2.5cT3cg0c2g0.lhe", "-3.5kt2cT0.5cg0c2g0.lhe", "-3.5kt2cT1.5cg0c2g0.lhe", "-3.5kt2cT2.0cg0c2g0.lhe", "-3.5kt2cT2.5cg0c2g0.lhe", "-5.0kt0.5cT0cg0c2g0.lhe", "-5.0kt1.0cT0cg0c2g0.lhe", "-5.0kt1.5cT-1cg0c2g0.lhe", "-5.0kt1.5cT0cg0c2g0.lhe", "-5.0kt2.0cT0cg0c2g0.lhe", "-5.0kt2.5cT0cg0c2g0.lhe", "-5kt1cT0cg-0.4c2g0.4.lhe", "-5kt1cT0cg-0.6c2g0.6.lhe", "-5kt1cT0cg-0.8c2g0.8.lhe", "-5kt1cT0cg-1c2g1.lhe", "-5kt1cT0cg0.2c2g-0.2.lhe", "-5kt1cT0cg0.4c2g-0.4.lhe", "-5kt1cT0cg0.6c2g-0.6.lhe", "-5kt1cT0cg0.8c2g-0.8.lhe", "-5kt1cT0cg0c2g0.lhe", "-5kt1cT0cg1c2g-1.lhe", "-7.5kt1.5cT-1cg0c2g0.lhe", "0.0001kt1cT0cg-0.2c2g0.2.lhe", "0.0001kt1cT0cg-0.4c2g0.4.lhe", "0.0001kt1cT0cg-0.6c2g0.6.lhe", "0.0001kt1cT0cg-0.8c2g0.8.lhe", "0.0001kt1cT0cg-1c2g1.lhe", "0.0001kt1cT0cg0.2c2g-0.2.lhe", "0.0001kt1cT0cg0.4c2g-0.4.lhe", "0.0001kt1cT0cg0.6c2g-0.6.lhe", "0.0001kt1cT0cg0.8c2g-0.8.lhe", "0.0001kt1cT0cg0c2g0.lhe", "0.0001kt1cT0cg1c2g-1.lhe", "1.0kt1.5cT-1cg0c2g0.lhe", "10kt1.5cT-1cg0c2g0.lhe", "12.5kt1.5cT-1cg0c2g0.lhe", "15kt1.5cT-1cg0c2g0.lhe", "1kt1cT-0.5cg-0.2c2g0.2.lhe", "1kt1cT-0.5cg-0.4c2g0.4.lhe", "1kt1cT-0.5cg-0.6c2g0.6.lhe", "1kt1cT-0.5cg-0.8c2g0.8.lhe", "1kt1cT-0.5cg-1c2g1.lhe", "1kt1cT-0.5cg0.2c2g-0.2.lhe", "1kt1cT-0.5cg0.4c2g-0.4.lhe", "1kt1cT-0.5cg0.6c2g-0.6.lhe", "1kt1cT-0.5cg0.8c2g-0.8.lhe", "1kt1cT-0.5cg0c2g0.lhe", "1kt1cT-0.5cg1c2g-1.lhe", "1kt1cT-1.5cg-0.2c2g0.2.lhe", "1kt1cT-1.5cg-0.4c2g0.4.lhe", "1kt1cT-1.5cg-0.6c2g0.6.lhe", "1kt1cT-1.5cg-0.8c2g0.8.lhe", "1kt1cT-1.5cg0.2c2g-0.2.lhe", "1kt1cT-1.5cg0.4c2g-0.4.lhe", "1kt1cT-1.5cg0.6c2g-0.6.lhe", "1kt1cT-1.5cg0.8c2g-0.8.lhe", "1kt1cT-1.5cg0c2g0.lhe", "1kt1cT-1.5cg1c2g-1.lhe", "1kt1cT-1cg-0.2c2g0.2.lhe", "1kt1cT-1cg-0.4c2g0.4.lhe", "1kt1cT-1cg-0.6c2g0.6.lhe", "1kt1cT-1cg-0.8c2g0.8.lhe", "1kt1cT-1cg0.2c2g-0.2.lhe", "1kt1cT-1cg0.4c2g-0.4.lhe", "1kt1cT-1cg0.6c2g-0.6.lhe", "1kt1cT-1cg0.8c2g-0.8.lhe", "1kt1cT-1cg0c2g0.lhe", "1kt1cT-1cg1c2g-1.lhe", "1kt1cT-2.5cg-0.2c2g0.2.lhe", "1kt1cT-2.5cg-0.4c2g0.4.lhe", "1kt1cT-2.5cg-0.6c2g0.6.lhe", "1kt1cT-2.5cg-0.8c2g0.8.lhe", "1kt1cT-2.5cg-1c2g1.lhe", "1kt1cT-2.5cg0.2c2g-0.2.lhe", "1kt1cT-2.5cg0.4c2g-0.4.lhe", "1kt1cT-2.5cg0.6c2g-0.6.lhe", "1kt1cT-2.5cg0.8c2g-0.8.lhe", "1kt1cT-2.5cg0c2g0.lhe", "1kt1cT-2.5cg1c2g-1.lhe", "1kt1cT-2cg-0.2c2g0.2.lhe", "1kt1cT-2cg-0.4c2g0.4.lhe", "1kt1cT-2cg-0.6c2g0.6.lhe", "1kt1cT-2cg-0.8c2g0.8.lhe", "1kt1cT-2cg0.2c2g-0.2.lhe", "1kt1cT-2cg0.4c2g-0.4.lhe", "1kt1cT-2cg0.6c2g-0.6.lhe", "1kt1cT-2cg0.8c2g-0.8.lhe", "1kt1cT-2cg0c2g0.lhe", "1kt1cT-2cg1c2g-1.lhe", "1kt1cT-3cg-0.2c2g0.2.lhe", "1kt1cT-3cg-0.4c2g0.4.lhe", "1kt1cT-3cg-0.6c2g0.6.lhe", "1kt1cT-3cg-0.8c2g0.8.lhe", "1kt1cT-3cg-1c2g1.lhe", "1kt1cT-3cg0.2c2g-0.2.lhe", "1kt1cT-3cg0.4c2g-0.4.lhe", "1kt1cT-3cg0.6c2g-0.6.lhe", "1kt1cT-3cg0.8c2g-0.8.lhe", "1kt1cT-3cg0c2g0.lhe", "1kt1cT-3cg1c2g-1.lhe", "1kt1cT0.5cg-0.2c2g0.2.lhe", "1kt1cT0.5cg-0.4c2g0.4.lhe", "1kt1cT0.5cg-0.6c2g0.6.lhe", "1kt1cT0.5cg-0.8c2g0.8.lhe", "1kt1cT0.5cg0.2c2g-0.2.lhe", "1kt1cT0.5cg0.4c2g-0.4.lhe", "1kt1cT0.5cg0.6c2g-0.6.lhe", "1kt1cT0.5cg0.8c2g-0.8.lhe", "1kt1cT0.5cg0c2g0.lhe", "1kt1cT0.5cg1c2g-1.lhe", "1kt1cT0cg-0.2c2g-0.2.lhe", "1kt1cT0cg-0.2c2g-0.4.lhe", "1kt1cT0cg-0.2c2g-0.6.lhe", "1kt1cT0cg-0.2c2g-0.8.lhe", "1kt1cT0cg-0.2c2g-1.lhe", "1kt1cT0cg-0.2c2g0.2.lhe", "1kt1cT0cg-0.2c2g0.4.lhe", "1kt1cT0cg-0.2c2g0.6.lhe", "1kt1cT0cg-0.2c2g0.8.lhe", "1kt1cT0cg-0.2c2g0.lhe", "1kt1cT0cg-0.2c2g1.lhe", "1kt1cT0cg-0.4c2g-0.2.lhe", "1kt1cT0cg-0.4c2g-0.4.lhe", "1kt1cT0cg-0.4c2g-0.6.lhe", "1kt1cT0cg-0.4c2g-0.8.lhe", "1kt1cT0cg-0.4c2g-1.lhe", "1kt1cT0cg-0.4c2g0.2.lhe", "1kt1cT0cg-0.4c2g0.4.lhe", "1kt1cT0cg-0.4c2g0.6.lhe", "1kt1cT0cg-0.4c2g0.8.lhe", "1kt1cT0cg-0.4c2g0.lhe", "1kt1cT0cg-0.4c2g1.lhe", "1kt1cT0cg-0.6c2g-0.2.lhe", "1kt1cT0cg-0.6c2g-0.4.lhe", "1kt1cT0cg-0.6c2g-0.6.lhe", "1kt1cT0cg-0.6c2g-0.8.lhe", "1kt1cT0cg-0.6c2g-1.lhe", "1kt1cT0cg-0.6c2g0.2.lhe", "1kt1cT0cg-0.6c2g0.4.lhe", "1kt1cT0cg-0.6c2g0.6.lhe", "1kt1cT0cg-0.6c2g0.8.lhe", "1kt1cT0cg-0.6c2g0.lhe", "1kt1cT0cg-0.6c2g1.lhe", "1kt1cT0cg-0.8c2g-0.2.lhe", "1kt1cT0cg-0.8c2g-0.4.lhe", "1kt1cT0cg-0.8c2g-0.6.lhe", "1kt1cT0cg-0.8c2g-0.8.lhe", "1kt1cT0cg-0.8c2g-1.lhe", "1kt1cT0cg-0.8c2g0.2.lhe", "1kt1cT0cg-0.8c2g0.4.lhe", "1kt1cT0cg-0.8c2g0.6.lhe", "1kt1cT0cg-0.8c2g0.8.lhe", "1kt1cT0cg-0.8c2g0.lhe", "1kt1cT0cg-0.8c2g1.lhe", "1kt1cT0cg-1.0c2g-0.2.lhe", "1kt1cT0cg-1c2g-0.2.lhe", "1kt1cT0cg-1c2g-0.4.lhe", "1kt1cT0cg-1c2g-0.6.lhe", "1kt1cT0cg-1c2g-0.8.lhe", "1kt1cT0cg-1c2g-1.lhe", "1kt1cT0cg-1c2g0.2.lhe", "1kt1cT0cg-1c2g0.4.lhe", "1kt1cT0cg-1c2g0.6.lhe", "1kt1cT0cg-1c2g0.8.lhe", "1kt1cT0cg-1c2g0.lhe", "1kt1cT0cg-1c2g1.lhe", "1kt1cT0cg0.0c2g-0.2.lhe", "1kt1cT0cg0.2c2g-0.2.lhe", "1kt1cT0cg0.2c2g-0.4.lhe", "1kt1cT0cg0.2c2g-0.6.lhe", "1kt1cT0cg0.2c2g-0.8.lhe", "1kt1cT0cg0.2c2g-1.lhe", "1kt1cT0cg0.2c2g0.2.lhe", "1kt1cT0cg0.2c2g0.4.lhe", "1kt1cT0cg0.2c2g0.6.lhe", "1kt1cT0cg0.2c2g0.8.lhe", "1kt1cT0cg0.2c2g0.lhe", "1kt1cT0cg0.2c2g1.lhe", "1kt1cT0cg0.4c2g-0.2.lhe", "1kt1cT0cg0.4c2g-0.4.lhe", "1kt1cT0cg0.4c2g-0.6.lhe", "1kt1cT0cg0.4c2g-0.8.lhe", "1kt1cT0cg0.4c2g-1.lhe", "1kt1cT0cg0.4c2g0.2.lhe", "1kt1cT0cg0.4c2g0.4.lhe", "1kt1cT0cg0.4c2g0.6.lhe", "1kt1cT0cg0.4c2g0.8.lhe", "1kt1cT0cg0.4c2g0.lhe", "1kt1cT0cg0.4c2g1.lhe", "1kt1cT0cg0.6c2g-0.2.lhe", "1kt1cT0cg0.6c2g-0.4.lhe", "1kt1cT0cg0.6c2g-0.6.lhe", "1kt1cT0cg0.6c2g-0.8.lhe", "1kt1cT0cg0.6c2g-1.lhe", "1kt1cT0cg0.6c2g0.2.lhe", "1kt1cT0cg0.6c2g0.4.lhe", "1kt1cT0cg0.6c2g0.6.lhe", "1kt1cT0cg0.6c2g0.8.lhe", "1kt1cT0cg0.6c2g0.lhe", "1kt1cT0cg0.6c2g1.lhe", "1kt1cT0cg0.8c2g-0.2.lhe", "1kt1cT0cg0.8c2g-0.4.lhe", "1kt1cT0cg0.8c2g-0.6.lhe", "1kt1cT0cg0.8c2g-0.8.lhe", "1kt1cT0cg0.8c2g-1.lhe", "1kt1cT0cg0.8c2g0.2.lhe", "1kt1cT0cg0.8c2g0.4.lhe", "1kt1cT0cg0.8c2g0.6.lhe", "1kt1cT0cg0.8c2g0.8.lhe", "1kt1cT0cg0.8c2g0.lhe", "1kt1cT0cg0.8c2g1.lhe", "1kt1cT0cg0c2g-0.2.lhe", "1kt1cT0cg0c2g-0.4.lhe", "1kt1cT0cg0c2g-0.6.lhe", "1kt1cT0cg0c2g-0.8.lhe", "1kt1cT0cg0c2g-1.lhe", "1kt1cT0cg0c2g0.2.lhe", "1kt1cT0cg0c2g0.4.lhe", "1kt1cT0cg0c2g0.6.lhe", "1kt1cT0cg0c2g0.8.lhe", "1kt1cT0cg0c2g0.lhe", "1kt1cT0cg0c2g1.lhe", "1kt1cT0cg1.0c2g-0.2.lhe", "1kt1cT0cg1c2g-0.2.lhe", "1kt1cT0cg1c2g-0.4.lhe", "1kt1cT0cg1c2g-0.6.lhe", "1kt1cT0cg1c2g-0.8.lhe", "1kt1cT0cg1c2g-1.lhe", "1kt1cT0cg1c2g0.2.lhe", "1kt1cT0cg1c2g0.4.lhe", "1kt1cT0cg1c2g0.6.lhe", "1kt1cT0cg1c2g0.8.lhe", "1kt1cT0cg1c2g0.lhe", "1kt1cT0cg1c2g1.lhe", "1kt1cT1.0cg-1c2g1.lhe", "1kt1cT1.5cg-0.2c2g0.2.lhe", "1kt1cT1.5cg-0.4c2g0.4.lhe", "1kt1cT1.5cg-0.6c2g0.6.lhe", "1kt1cT1.5cg-0.8c2g0.8.lhe", "1kt1cT1.5cg-1c2g1.lhe", "1kt1cT1.5cg0.2c2g-0.2.lhe", "1kt1cT1.5cg0.4c2g-0.4.lhe", "1kt1cT1.5cg0.6c2g-0.6.lhe", "1kt1cT1.5cg0.8c2g-0.8.lhe", "1kt1cT1.5cg0c2g0.lhe", "1kt1cT1.5cg1c2g-1.lhe", "1kt1cT1cg-0.2c2g0.2.lhe", "1kt1cT1cg-0.4c2g0.4.lhe", "1kt1cT1cg-0.6c2g0.6.lhe", "1kt1cT1cg-0.8c2g0.8.lhe", "1kt1cT1cg0.2c2g-0.2.lhe", "1kt1cT1cg0.4c2g-0.4.lhe", "1kt1cT1cg0.6c2g-0.6.lhe", "1kt1cT1cg0.8c2g-0.8.lhe", "1kt1cT1cg0c2g0.lhe", "1kt1cT1cg1c2g-1.lhe", "1kt1cT2.0cg-1c2g1.lhe", "1kt1cT2.5cg-0.2c2g0.2.lhe", "1kt1cT2.5cg-0.4c2g0.4.lhe", "1kt1cT2.5cg-0.6c2g0.6.lhe", "1kt1cT2.5cg-0.8c2g0.8.lhe", "1kt1cT2.5cg-1c2g1.lhe", "1kt1cT2.5cg0.2c2g-0.2.lhe", "1kt1cT2.5cg0.4c2g-0.4.lhe", "1kt1cT2.5cg0.6c2g-0.6.lhe", "1kt1cT2.5cg0.8c2g-0.8.lhe", "1kt1cT2.5cg0c2g0.lhe", "1kt1cT2.5cg1c2g-1.lhe", "1kt1cT2cg-0.2c2g0.2.lhe", "1kt1cT2cg-0.4c2g0.4.lhe", "1kt1cT2cg-0.6c2g0.6.lhe", "1kt1cT2cg-0.8c2g0.8.lhe", "1kt1cT2cg0.2c2g-0.2.lhe", "1kt1cT2cg0.4c2g-0.4.lhe", "1kt1cT2cg0.6c2g-0.6.lhe", "1kt1cT2cg0.8c2g-0.8.lhe", "1kt1cT2cg0c2g0.lhe", "1kt1cT2cg1c2g-1.lhe", "1kt1cT3cg-0.2c2g0.2.lhe", "1kt1cT3cg-0.4c2g0.4.lhe", "1kt1cT3cg-0.6c2g0.6.lhe", "1kt1cT3cg-0.8c2g0.8.lhe", "1kt1cT3cg0.2c2g-0.2.lhe", "1kt1cT3cg0.4c2g-0.4.lhe", "1kt1cT3cg0.6c2g-0.6.lhe", "1kt1cT3cg0.8c2g-0.8.lhe", "1kt1cT3cg0c2g0.lhe", "1kt1cT3cg1c2g-1.lhe", "2.4kt1.5cT-1cg0c2g0.lhe", "2.4kt1cT0cg-0.2c2g0.2.lhe", "2.4kt1cT0cg-0.4c2g0.4.lhe", "2.4kt1cT0cg-0.6c2g0.6.lhe", "2.4kt1cT0cg-0.8c2g0.8.lhe", "2.4kt1cT0cg-1c2g1.lhe", "2.4kt1cT0cg0.2c2g-0.2.lhe", "2.4kt1cT0cg0.4c2g-0.4.lhe", "2.4kt1cT0cg0.6c2g-0.6.lhe", "2.4kt1cT0cg0.8c2g-0.8.lhe", "2.4kt1cT0cg0c2g0.lhe", "2.4kt1cT0cg1c2g-1.lhe", "3.5kt0.5cT-0.5cg0c2g0.lhe", "3.5kt0.5cT-1cg0c2g0.lhe", "3.5kt0.5cT-2cg0c2g0.lhe", "3.5kt0.5cT-3cg0c2g0.lhe", "3.5kt0.5cT0.0cg0c2g0.lhe", "3.5kt0.5cT1cg0c2g0.lhe", "3.5kt0.5cT2.5cg0c2g0.lhe", "3.5kt0.5cT2cg0c2g0.lhe", "3.5kt0.5cT3cg0c2g0.lhe", "3.5kt1.0cT0.5cg0c2g0.lhe", "3.5kt1.0cT2.5cg0c2g0.lhe", "3.5kt1.5cT-0.5cg0c2g0.lhe", "3.5kt1.5cT-1cg0c2g0.lhe", "3.5kt1.5cT-2cg0c2g0.lhe", "3.5kt1.5cT-3cg0c2g0.lhe", "3.5kt1.5cT0.5cg0c2g0.lhe", "3.5kt1.5cT1cg0c2g0.lhe", "3.5kt1.5cT2cg0c2g0.lhe", "3.5kt1.5cT3cg0c2g0.lhe", "3.5kt2.0cT-0.5cg0c2g0.lhe", "3.5kt2.0cT-1cg0c2g0.lhe", "3.5kt2.0cT-2cg0c2g0.lhe", "3.5kt2.0cT-3cg0c2g0.lhe", "3.5kt2.0cT0.5cg0c2g0.lhe", "3.5kt2.0cT1cg0c2g0.lhe", "3.5kt2.0cT2cg0c2g0.lhe", "3.5kt2.0cT3cg0c2g0.lhe", "3.5kt2.5cT-0.5cg0c2g0.lhe", "3.5kt2.5cT-1cg0c2g0.lhe", "3.5kt2.5cT-2cg0c2g0.lhe", "3.5kt2.5cT-3cg0c2g0.lhe", "3.5kt2.5cT0.5cg0c2g0.lhe", "3.5kt2.5cT1cg0c2g0.lhe", "3.5kt2.5cT2cg0c2g0.lhe", "3.5kt2.5cT3cg0c2g0.lhe", "3.5kt2cT0.5cg0c2g0.lhe", "3.5kt2cT1.5cg0c2g0.lhe", "3.5kt2cT2.0cg0c2g0.lhe", "3.5kt2cT2.5cg0c2g0.lhe", "5.0kt1.5cT-1cg0c2g0.lhe", "5kt1cT0cg-0.2c2g0.2.lhe", "5kt1cT0cg-0.4c2g0.4.lhe", "5kt1cT0cg-0.6c2g0.6.lhe", "5kt1cT0cg-0.8c2g0.8.lhe", "5kt1cT0cg-1c2g1.lhe", "5kt1cT0cg0.2c2g-0.2.lhe", "5kt1cT0cg0.4c2g-0.4.lhe", "5kt1cT0cg0.6c2g-0.6.lhe", "5kt1cT0cg0.8c2g-0.8.lhe", "5kt1cT0cg0c2g0.lhe", "5kt1cT0cg1c2g-1.lhe", "7.5kt-1cT1.5cg0c2g0.lhe", "7.5kt1.5cT-1cg0c2g0.lhe"};
 /*   string namefile[123] ={"L1kt1cT-0.5cg0c2g-0.2.lhe",
    "L1kt1cT-0.5cg0c2g-0.4.lhe",
    "L1kt1cT-0.5cg0c2g-0.6.lhe",
    "L1kt1cT-0.5cg0c2g-0.8.lhe",
    "L1kt1cT-0.5cg0c2g0.2.lhe",
    "L1kt1cT-0.5cg0c2g0.4.lhe",
    "L1kt1cT-0.5cg0c2g0.6.lhe",
    "L1kt1cT-0.5cg0c2g0.8.lhe",
    "L1kt1cT-0.5cg0c2g1.lhe",
    "L1kt1cT-1.5cg0c2g-0.2.lhe",
    "L1kt1cT-1.5cg0c2g-0.4.lhe",
    "L1kt1cT-1.5cg0c2g-0.6.lhe",
    "L1kt1cT-1.5cg0c2g-0.8.lhe",
    "L1kt1cT-1.5cg0c2g-1.lhe",
    "L1kt1cT-1.5cg0c2g0.2.lhe",
    "L1kt1cT-1.5cg0c2g0.4.lhe",
    "L1kt1cT-1.5cg0c2g0.6.lhe",
    "L1kt1cT-1.5cg0c2g0.8.lhe",
    "L1kt1cT-1.5cg0c2g0.lhe",
    "L1kt1cT-1cg0c2g-0.2.lhe",
    "L1kt1cT-1cg0c2g-0.4.lhe",
    "L1kt1cT-1cg0c2g-0.6.lhe",
    "L1kt1cT-1cg0c2g-0.8.lhe",
    "L1kt1cT-1cg0c2g-1.lhe",
    "L1kt1cT-1cg0c2g0.4.lhe",
    "L1kt1cT-1cg0c2g0.6.lhe",
    "L1kt1cT-1cg0c2g0.8.lhe",
    "L1kt1cT-1cg0c2g0.lhe",
    "L1kt1cT-2.5cg0c2g-0.2.lhe",
    "L1kt1cT-2.5cg0c2g-0.4.lhe",
    "L1kt1cT-2.5cg0c2g-0.6.lhe",
    "L1kt1cT-2.5cg0c2g-0.8.lhe",
    "L1kt1cT-2.5cg0c2g-1.lhe",
    "L1kt1cT-2.5cg0c2g0.2.lhe",
    "L1kt1cT-2.5cg0c2g0.4.lhe",
    "L1kt1cT-2.5cg0c2g0.6.lhe",
    "L1kt1cT-2.5cg0c2g0.8.lhe",
    "L1kt1cT-2.5cg0c2g0.lhe",
    "L1kt1cT-2.5cg0c2g1.lhe",
    "L1kt1cT-2cg0c2g-0.2.lhe",
    "L1kt1cT-2cg0c2g-0.6.lhe",
    "L1kt1cT-2cg0c2g-0.8.lhe",
    "L1kt1cT-2cg0c2g-1.lhe",
    "L1kt1cT-2cg0c2g0.2.lhe",
    "L1kt1cT-2cg0c2g0.4.lhe",
    "L1kt1cT-2cg0c2g0.6.lhe",
    "L1kt1cT-2cg0c2g0.8.lhe",
    "L1kt1cT-2cg0c2g0.lhe",
    "L1kt1cT-3cg0c2g-0.2.lhe",
    "L1kt1cT-3cg0c2g-0.4.lhe",
    "L1kt1cT-3cg0c2g-0.6.lhe",
    "L1kt1cT-3cg0c2g-0.8.lhe",
    "L1kt1cT-3cg0c2g-1.lhe",
    "L1kt1cT-3cg0c2g0.2.lhe",
    "L1kt1cT-3cg0c2g0.4.lhe",
    "L1kt1cT-3cg0c2g0.6.lhe",
    "L1kt1cT-3cg0c2g0.8.lhe",
    "L1kt1cT-3cg0c2g0.lhe",
    "L1kt1cT-3cg0c2g1.lhe",
    "L1kt1cT0.5cg0c2g-0.2.lhe",
    "L1kt1cT0.5cg0c2g-0.4.lhe",
    "L1kt1cT0.5cg0c2g-0.6.lhe",
    "L1kt1cT0.5cg0c2g-0.8.lhe",
    "L1kt1cT0.5cg0c2g-1.lhe",
    "L1kt1cT0.5cg0c2g0.2.lhe",
    "L1kt1cT0.5cg0c2g0.4.lhe",
    "L1kt1cT0.5cg0c2g0.6.lhe",
    "L1kt1cT0.5cg0c2g0.8.lhe",
    "L1kt1cT0.5cg0c2g0.lhe",
    "L1kt1cT0cg0c2g0.lhe",
    "L1kt1cT1.0cg0c2g1.lhe",
    "L1kt1cT1.5cg0c2g-0.2.lhe",
    "L1kt1cT1.5cg0c2g-0.4.lhe",
    "L1kt1cT1.5cg0c2g-0.6.lhe",
    "L1kt1cT1.5cg0c2g-0.8.lhe",
    "L1kt1cT1.5cg0c2g-1.lhe",
    "L1kt1cT1.5cg0c2g0.2.lhe",
    "L1kt1cT1.5cg0c2g0.4.lhe",
    "L1kt1cT1.5cg0c2g0.6.lhe",
    "L1kt1cT1.5cg0c2g0.8.lhe",
    "L1kt1cT1.5cg0c2g0.lhe",
    "L1kt1cT1.5cg0c2g1.lhe",
    "L1kt1cT1cg0c2g-0.2.lhe",
    "L1kt1cT1cg0c2g-0.6.lhe",
    "L1kt1cT1cg0c2g-0.8.lhe",
    "L1kt1cT1cg0c2g-1.lhe",
    "L1kt1cT1cg0c2g0.2.lhe",
    "L1kt1cT1cg0c2g0.4.lhe",
    "L1kt1cT1cg0c2g0.6.lhe",
    "L1kt1cT1cg0c2g0.8.lhe",
    "L1kt1cT1cg0c2g0.lhe",
    "L1kt1cT2.0cg0c2g1.lhe",
    "L1kt1cT2.5cg0c2g-0.2.lhe",
    "L1kt1cT2.5cg0c2g-0.4.lhe",
    "L1kt1cT2.5cg0c2g-0.6.lhe",
    "L1kt1cT2.5cg0c2g-0.8.lhe",
    "L1kt1cT2.5cg0c2g-1.lhe",
    "L1kt1cT2.5cg0c2g0.2.lhe",
    "L1kt1cT2.5cg0c2g0.4.lhe",
    "L1kt1cT2.5cg0c2g0.6.lhe",
    "L1kt1cT2.5cg0c2g0.8.lhe",
    "L1kt1cT2.5cg0c2g0.lhe",
    "L1kt1cT2.5cg0c2g1.lhe",
    "L1kt1cT2cg0c2g-0.2.lhe",
    "L1kt1cT2cg0c2g-0.4.lhe",
    "L1kt1cT2cg0c2g-0.6.lhe",
    "L1kt1cT2cg0c2g-0.8.lhe",
    "L1kt1cT2cg0c2g-1.lhe",
    "L1kt1cT2cg0c2g0.2.lhe",
    "L1kt1cT2cg0c2g0.4.lhe",
    "L1kt1cT2cg0c2g0.6.lhe",
    "L1kt1cT2cg0c2g0.8.lhe",
    "L1kt1cT2cg0c2g0.lhe",
    "L1kt1cT3cg0c2g-0.2.lhe",
    "L1kt1cT3cg0c2g-0.4.lhe",
    "L1kt1cT3cg0c2g-0.6.lhe",
    "L1kt1cT3cg0c2g-0.8.lhe",
    "L1kt1cT3cg0c2g-1.lhe",
    "L1kt1cT3cg0c2g0.2.lhe",
    "L1kt1cT3cg0c2g0.4.lhe",
    "L1kt1cT3cg0c2g0.6.lhe",
    "L1kt1cT3cg0c2g0.8.lhe",
    "L1kt1cT3cg0c2g0.lhe"};
  */
    /*
    string namefile[109] ={"L1kt1cT-0.5cg0c2g-0.2.lhe",
        "L1kt1cT-0.5cg0c2g-0.4.lhe",
        "L1kt1cT-0.5cg0c2g-0.6.lhe",
        "L1kt1cT-0.5cg0c2g-0.8.lhe",
        "L1kt1cT-0.5cg0c2g0.2.lhe",
        "L1kt1cT-0.5cg0c2g0.4.lhe",
        "L1kt1cT-0.5cg0c2g0.6.lhe",
        "L1kt1cT-0.5cg0c2g0.8.lhe",
        "L1kt1cT-0.5cg0c2g1.lhe",
        "L1kt1cT-1.5cg0c2g-0.2.lhe",
        "L1kt1cT-1.5cg0c2g-0.4.lhe",
        "L1kt1cT-1.5cg0c2g-0.6.lhe",
        "L1kt1cT-1.5cg0c2g-0.8.lhe",
        "L1kt1cT-1.5cg0c2g-1.lhe",
        "L1kt1cT-1.5cg0c2g0.2.lhe",
        "L1kt1cT-1.5cg0c2g0.4.lhe",
        "L1kt1cT-1.5cg0c2g0.6.lhe",
        "L1kt1cT-1.5cg0c2g0.8.lhe",
        "L1kt1cT-1.5cg0c2g0.lhe",
        "L1kt1cT-1cg0c2g-0.2.lhe",
        "L1kt1cT-1cg0c2g-0.4.lhe",
        "L1kt1cT-1cg0c2g-0.6.lhe",
        "L1kt1cT-1cg0c2g-0.8.lhe",
        "L1kt1cT-1cg0c2g-1.lhe",
        "L1kt1cT-1cg0c2g0.4.lhe",
        "L1kt1cT-1cg0c2g0.6.lhe",
        "L1kt1cT-1cg0c2g0.8.lhe",
        "L1kt1cT-1cg0c2g0.lhe",
        "L1kt1cT-2.5cg0c2g-0.2.lhe",
        "L1kt1cT-2.5cg0c2g-0.4.lhe",
        "L1kt1cT-2.5cg0c2g-0.6.lhe",
        "L1kt1cT-2.5cg0c2g-0.8.lhe",
        "L1kt1cT-2.5cg0c2g-1.lhe",
        "L1kt1cT-2.5cg0c2g0.2.lhe",
        "L1kt1cT-2.5cg0c2g0.4.lhe",
        "L1kt1cT-2.5cg0c2g0.6.lhe",
        "L1kt1cT-2.5cg0c2g0.8.lhe",
        "L1kt1cT-2.5cg0c2g0.lhe",
        "L1kt1cT-2.5cg0c2g1.lhe",
        "L1kt1cT-2cg0c2g-0.2.lhe",
        "L1kt1cT-2cg0c2g-0.6.lhe",
        "L1kt1cT-2cg0c2g-0.8.lhe",
        "L1kt1cT-2cg0c2g-1.lhe",
        "L1kt1cT-2cg0c2g0.2.lhe",
        "L1kt1cT-2cg0c2g0.4.lhe",
        "L1kt1cT-2cg0c2g0.6.lhe",
        "L1kt1cT-2cg0c2g0.8.lhe",
        "L1kt1cT-2cg0c2g0.lhe",
        "L1kt1cT-3cg0c2g-0.2.lhe",
        "L1kt1cT-3cg0c2g-0.4.lhe",
        "L1kt1cT-3cg0c2g-0.6.lhe",
        "L1kt1cT-3cg0c2g-0.8.lhe",
        "L1kt1cT-3cg0c2g-1.lhe",
        "L1kt1cT-3cg0c2g0.2.lhe",
        "L1kt1cT-3cg0c2g0.4.lhe",
        "L1kt1cT-3cg0c2g0.6.lhe",
        "L1kt1cT-3cg0c2g0.8.lhe",
        "L1kt1cT-3cg0c2g0.lhe",
        "L1kt1cT-3cg0c2g1.lhe",
        "L1kt1cT0.5cg0c2g-1.lhe",
        "L1kt1cT0.5cg0c2g0.2.lhe",
        "L1kt1cT0.5cg0c2g0.4.lhe",
        "L1kt1cT0.5cg0c2g0.6.lhe",
        "L1kt1cT0.5cg0c2g0.8.lhe",
        "L1kt1cT0cg0c2g0.lhe",
        "L1kt1cT1.0cg0c2g1.lhe",
        "L1kt1cT1.5cg0c2g-0.2.lhe",
        "L1kt1cT1.5cg0c2g-0.4.lhe",
        "L1kt1cT1.5cg0c2g-0.6.lhe",
        "L1kt1cT1.5cg0c2g-0.8.lhe",
        "L1kt1cT1.5cg0c2g-1.lhe",
        "L1kt1cT1.5cg0c2g0.2.lhe",
        "L1kt1cT1.5cg0c2g0.4.lhe",
        "L1kt1cT1.5cg0c2g0.6.lhe",
        "L1kt1cT1.5cg0c2g0.8.lhe",
        "L1kt1cT1.5cg0c2g0.lhe",
        "L1kt1cT1.5cg0c2g1.lhe",
        "L1kt1cT2.0cg0c2g1.lhe",
        "L1kt1cT2.5cg0c2g-0.2.lhe",
        "L1kt1cT2.5cg0c2g-0.4.lhe",
        "L1kt1cT2.5cg0c2g-0.6.lhe",
        "L1kt1cT2.5cg0c2g-0.8.lhe",
        "L1kt1cT2.5cg0c2g-1.lhe",
        "L1kt1cT2.5cg0c2g0.2.lhe",
        "L1kt1cT2.5cg0c2g0.4.lhe",
        "L1kt1cT2.5cg0c2g0.6.lhe",
        "L1kt1cT2.5cg0c2g0.8.lhe",
        "L1kt1cT2.5cg0c2g0.lhe",
        "L1kt1cT2.5cg0c2g1.lhe",
        "L1kt1cT2cg0c2g-0.2.lhe",
        "L1kt1cT2cg0c2g-0.4.lhe",
        "L1kt1cT2cg0c2g-0.6.lhe",
        "L1kt1cT2cg0c2g-0.8.lhe",
        "L1kt1cT2cg0c2g-1.lhe",
        "L1kt1cT2cg0c2g0.2.lhe",
        "L1kt1cT2cg0c2g0.4.lhe",
        "L1kt1cT2cg0c2g0.6.lhe",
        "L1kt1cT2cg0c2g0.8.lhe",
        "L1kt1cT2cg0c2g0.lhe",
        "L1kt1cT3cg0c2g-0.2.lhe",
        "L1kt1cT3cg0c2g-0.4.lhe",
        "L1kt1cT3cg0c2g-0.6.lhe",
        "L1kt1cT3cg0c2g-0.8.lhe",
        "L1kt1cT3cg0c2g-1.lhe",
        "L1kt1cT3cg0c2g0.2.lhe",
        "L1kt1cT3cg0c2g0.4.lhe",
        "L1kt1cT3cg0c2g0.6.lhe",
        "L1kt1cT3cg0c2g0.8.lhe",
        "L1kt1cT3cg0c2g0.lhe"};
     */
    //
    /*
    string namefile[187] ={"L1kt1cT0.5cg0c2g0.2.lhe",
        "L1kt0.25cT0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg0.2c2g-0.2.lhe",
        "L-7.5kt1cT0cg0.2c2g-0.2.lhe",
        "L1kt1cT0.5cg0c2g0.4.lhe",
        "L1kt1.25cT0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg0.4c2g-0.4.lhe",
        "L-7.5kt1cT0cg0.4c2g-0.4.lhe",
        "L1kt1cT0.5cg0c2g0.6.lhe",
        "L1kt1.75cT0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg0.6c2g-0.6.lhe",
        "L-7.5kt1cT0cg0.6c2g-0.6.lhe",
        "L1kt1cT0.5cg0c2g0.8.lhe",
        "L1kt2.25cT0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg0.8c2g-0.8.lhe",
        "L-7.5kt1cT0cg0.8c2g-0.8.lhe",
        "L1kt1cT0.5cg0c2g-0.2.lhe",
        "L1kt0.25cT-0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg1c2g-1.lhe",
        "L-7.5kt1cT0cg1c2g-1.lhe",
        "L1kt1cT0.5cg0c2g-0.4.lhe",
        "L1kt1.25cT-0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg-0.4c2g0.2.lhe",
        "L-7.5kt1cT0cg-0.2c2g0.2.lhe",
        "L1kt1cT0.5cg0c2g-0.6.lhe",
        "L1kt1.75cT-0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg-0.4c2g0.4.lhe",
        "L-7.5kt1cT0cg-0.4c2g0.4.lhe",
        "L1kt1cT0.5cg0c2g-0.8.lhe",
        "L1kt2.25cT-0.5cg0c2g0.lhe",
        "L3.5kt1cT0cg-0.4c2g0.6.lhe",
        "L-7.5kt1cT0cg-0.6c2g0.6.lhe",
        "L1kt1cT1cg0c2g0.2.lhe",
        "L1kt0.25cT1.5cg0c2g0.lhe",
        "L3.5kt1cT0cg-0.4c2g0.8.lhe",
        "L-7.5kt1cT0cg-0.8c2g0.8.lhe",
        "L1kt1cT1cg0c2g0.4.lhe",
        "L1kt1.25cT1.5cg0c2g0.lhe",
        "L3.5kt1cT0cg-0.4c2g1.lhe",
        "L-7.5kt1cT0cg-1c2g1.lhe",
        "L1kt1cT1cg0c2g0.6.lhe",
        "L1kt1.75cT1.5cg0c2g0.lhe",
        "L7.5kt1cT0cg0.2c2g-0.2.lhe",
        "L-10kt1cT0cg0.2c2g-0.2.lhe",
        "L1kt1cT1cg0c2g0.8.lhe",
        "L1kt2.25cT1.5cg0c2g0.lhe",
        "L7.5kt1cT0cg0.4c2g-0.4.lhe",
        "L-10kt1cT0cg0.4c2g-0.4.lhe",
        "L1kt1cT1cg0c2g-0.2.lhe",
        "L1kt0.25cT1cg0c2g0.lhe",
        "L7.5kt1cT0cg0.6c2g-0.6.lhe",
        "L-10kt1cT0cg0.6c2g-0.6.lhe",
        "L1kt1cT1cg0c2g-0.4.lhe",
        "L1kt1.25cT1cg0c2g0.lhe",
        "L7.5kt1cT0cg0.8c2g-0.8.lhe",
        "L-10kt1cT0cg0.8c2g-0.8.lhe",
        "L1kt1cT1cg0c2g-0.6.lhe",
        "L1kt1.75cT1cg0c2g0.lhe",
        "L7.5kt1cT0cg1c2g-1.lhe",
        "L-10kt1cT0cg1c2g-1.lhe",
        "L1kt1cT1cg0c2g-0.8.lhe",
        "L1kt2.25cT1cg0c2g0.lhe",
        "L7.5kt1cT0cg-0.2c2g0.2.lhe",
        "L-10kt1cT0cg-0.2c2g0.2.lhe",
        "L1kt1cT2cg0c2g0.2.lhe",
        "L7.5kt1cT0cg-0.4c2g0.4.lhe",
        "L-10kt1cT0cg-0.4c2g0.4.lhe",
        "L1kt1cT2cg0c2g0.4.lhe",
        "L7.5kt1cT0cg-0.6c2g0.6.lhe",
        "L-10kt1cT0cg-0.6c2g0.6.lhe",
        "L1kt1cT2cg0c2g0.6.lhe",
        "L7.5kt1cT0cg-0.8c2g0.8.lhe",
        "L-10kt1cT0cg-0.8c2g0.8.lhe",
        "L1kt1cT2cg0c2g0.8.lhe",
        "L7.5kt1cT0cg-1c2g1.lhe",
        "L-10kt1cT0cg-1c2g1.lhe",
        "L1kt1cT2cg0c2g-0.2.lhe",
        "L1kt0.5cT1.5cg0c2g0.lhe",
        "L10kt1cT0cg0.2c2g-0.2.lhe",
        "L1kt1cT2cg0c2g-0.4.lhe",
        "L-12.5kt1cT0cg0.2c2g-0.2.lhe",
        "L1kt1.5cT1.5cg0c2g0.lhe",
        "L10kt1cT0cg0.4c2g-0.4.lhe",
        "L1kt1cT2cg0c2g-0.6.lhe",
        "L-12.5kt1cT0cg0.4c2g-0.4.lhe",
        "L1kt2cT1.5cg0c2g0.lhe",
        "L10kt1cT0cg0.6c2g-0.6.lhe",
        "L1kt1cT2cg0c2g-0.8.lhe",
        "L-12.5kt1cT0cg0.6c2g-0.6.lhe",
        "L1kt2.5cT1.5cg0c2g0.lhe",
        "L10kt1cT0cg0.8c2g-0.8.lhe",
        "L1kt1cT3cg0c2g0.2.lhe",
        "L1kt0.25cT2cg0c2g0.lhe",
        "L-12.5kt1cT0cg0.8c2g-0.8.lhe",
        "L10kt1cT0cg1c2g-1.lhe",
        "L1kt1cT3cg0c2g0.4.lhe",
        "L1kt1.25cT2cg0c2g0.lhe",
        "L-12.5kt1cT0cg1c2g-1.lhe",
        "L10kt1cT0cg-0.2c2g0.2.lhe",
        "L1kt1cT3cg0c2g0.6.lhe",
        "L1kt1.75cT2cg0c2g0.lhe",
        "L-12.5kt1cT0cg-0.2c2g0.2.lhe",
        "L10kt1cT0cg-0.4c2g0.4.lhe",
        "L1kt1cT3cg0c2g0.8.lhe",
        "L1kt2.25cT2cg0c2g0.lhe",
        "L-12.5kt1cT0cg-0.4c2g0.4.lhe",
        "L1kt1cT3cg0c2g-0.2.lhe",
        "L10kt1cT0cg-0.6c2g0.6.lhe",
        "L12.5kt2.5cT0cg0c2g0.lhe",
        "L-12.5kt1cT0cg-0.6c2g0.6.lhe",
        "L1kt1cT3cg0c2g-0.4.lhe",
        "L10kt1cT0cg-0.8c2g0.8.lhe",
        "L1kt1cT0cg-1c2g1.lhe",
        "L-12.5kt1cT0cg-0.8c2g0.8.lhe",
        "L10kt1cT0cg-1c2g1.lhe",
        "L1kt1cT3cg0c2g-0.6.lhe",
        "L1kt1cT0cg-1.5c2g1.lhe",
        "L-12.5kt1cT0cg-1c2g1.lhe",
        "L1kt1cT3cg0c2g-0.8.lhe",
        "L12.5kt1cT0cg0.2c2g-0.2.lhe",
        "L1kt1cT0cg-2c2g1.lhe",
        "L-15kt1cT0cg0.2c2g-0.2.lhe",
        "L1kt1cT-1cg0c2g0.2.lhe",
        "L12.5kt1cT0cg0.4c2g-0.4.lhe",
        "L1kt1cT0cg-2.5c2g1.lhe",
        "L-15kt1cT0cg0.4c2g-0.4.lhe",
        "L1kt1cT-1cg0c2g0.4.lhe",
        "L12.5kt1cT0cg0.6c2g-0.6.lhe",
        "L3.5kt1cT-0.5cg0c2g0.lhe",
        "L-15kt1cT0cg0.6c2g-0.6.lhe",
        "L1kt1cT-1cg0c2g0.6.lhe",
        "L12.5kt1cT0cg0.8c2g-0.8.lhe",
        "L3.5kt1cT-1cg0c2g0.lhe",
        "L-15kt1cT0cg0.8c2g-0.8.lhe",
        "L1kt1cT-1cg0c2g0.8.lhe",
        "L3.5kt1cT-2cg0c2g0.lhe",
        "L12.5kt1cT0cg1c2g-1.lhe",
        "L-15kt1cT0cg1c2g-1.lhe",
        "L1kt1cT-1cg0c2g-0.2.lhe",
        "L3.5kt1cT-3cg0c2g0.lhe",
        "L12.5kt1cT0cg-0.2c2g0.2.lhe",
        "L-15kt1cT0cg-0.2c2g0.2.lhe",
        "L1kt1cT-1cg0c2g-0.4.lhe",
        "L3.5kt0.5cT1cg0c2g0.lhe",
        "L12.5kt1cT0cg-0.4c2g0.4.lhe",
        "L-15kt1cT0cg-0.4c2g0.4.lhe",
        "L1kt1cT-1cg0c2g-0.6.lhe",
        "L3.5kt1cT1cg0c2g0.lhe",
        "L12.5kt1cT0cg-0.6c2g0.6.lhe",
        "L-15kt1cT0cg-0.6c2g0.6.lhe",
        "L1kt1cT-1cg0c2g-0.8.lhe",
        "L-3.5kt1cT-0.5cg0c2g0.lhe",
        "L12.5kt1cT0cg-0.8c2g0.8.lhe",
        "L-15kt1cT0cg-0.8c2g0.8.lhe",
        "L1kt1cT-2cg0c2g0.2.lhe",
        "L-3.5kt1cT-1cg0c2g0.lhe",
        "L12.5kt1cT0cg-1c2g1.lhe",
        "L-15kt1cT0cg-1c2g1.lhe",
        "L1kt1cT-2cg0c2g0.4.lhe",
        "L-3.5kt1cT-2cg0c2g0.lhe",
        "L15kt1cT0cg0.2c2g-0.2.lhe",
        "L1kt1cT-2cg0c2g0.6.lhe",
        "L-3.5kt1cT-3cg0c2g0.lhe",
        "L15kt1cT0cg0.4c2g-0.4.lhe",
        "L1kt1cT-2cg0c2g0.8.lhe",
        "L-3.5kt1cT1cg0c2g0.lhe",
        "L15kt1cT0cg0.6c2g-0.6.lhe",
        "L1kt1cT-2cg0c2g-0.2.lhe",
        "L-3.5kt1cT3cg0c2g0.lhe",
        "L15kt1cT0cg0.8c2g-0.8.lhe",
        "L1kt1cT-2cg0c2g-0.4.lhe",
        "L15kt1cT0cg1c2g-1.lhe",
        "L1kt1cT-2cg0c2g-0.6.lhe",
        "L15kt1cT0cg-0.2c2g0.2.lhe",
        "L1kt1cT-2cg0c2g-0.8.lhe",
        "L15kt1cT0cg-0.4c2g0.4.lhe",
        "L1kt1cT-3cg0c2g0.2.lhe",
        "L15kt1cT0cg-0.6c2g0.6.lhe",
        "L1kt1cT-3cg0c2g0.4.lhe",
        "L15kt1cT0cg-0.8c2g0.8.lhe",
        "L1kt1cT-3cg0c2g0.6.lhe",
        "L15kt1cT0cg-1c2g1.lhe",
        "L1kt1cT-3cg0c2g0.8.lhe",
        "L1kt1cT-3cg0c2g-0.2.lhe",
        "L1kt1cT-3cg0c2g-0.4.lhe",
        "L1kt1cT-3cg0c2g-0.6.lhe",
        "L1kt1cT-3cg0c2g-0.8.lhe"};
     */
    /*
     string namefile[33] ={"L-5kt1cT0cg-0.2c2g0.2.lhe",
        "L-5kt1cT0cg0c2g0.lhe",
        "L-7.5kt1cT0cg0c2g0.lhe",
        "L1kt0.25cT-0.5cg0c2g0.lhe",
        "L1kt0.25cT0.5cg0c2g0.lhe",
        "L1kt0.25cT1.5cg0c2g0.lhe",
        "L1kt0.25cT1cg0c2g0.lhe",
        "L1kt0.25cT2cg0c2g0.lhe",
        "L1kt1cT-1.5cg-1c2g1.lhe",
        "L1kt1cT-1.5cg0c2g-0.2.lhe",
        "L1kt1cT-1.5cg0c2g-0.4.lhe",
        "L1kt1cT-1.5cg0c2g-0.6.lhe",
        "L1kt1cT-1.5cg0c2g-0.8.lhe",
        "L1kt1cT-1.5cg0c2g-1.lhe",
        "L1kt1cT-1.5cg0c2g0.2.lhe",
        "L1kt1cT-1cg-1c2g1.lhe",
        "L1kt1cT-1cg0c2g1.lhe",
        "L1kt1cT-2cg-1c2g1.lhe",
        "L1kt1cT-2cg0c2g1.lhe",
        "L1kt1cT0.5cg-1c2g1.lhe",
        "L1kt1cT0.5cg0c2g-0.2.lhe",
        "L1kt1cT0.5cg0c2g-0.4.lhe",
        "L1kt1cT0.5cg0c2g-0.6.lhe",
        "L1kt1cT0.5cg0c2g-0.8.lhe",
        "L1kt1cT0.5cg0c2g-1.lhe",
        "L1kt1cT0.5cg0c2g0.2.lhe",
        "L1kt1cT0.5cg0c2g0.4.lhe",
        "L1kt1cT0.5cg0c2g0.6.lhe",
        "L1kt1cT0.5cg0c2g0.8.lhe",
        "L1kt1cT0.5cg0c2g1.lhe",
        "L1kt1cT0cg0c2g-1.lhe",
        "L1kt1cT3cg-1c2g1.lhe",
        "L1kt1cT3cg0c2g1.lhe"};
     */

    /*string namefile[2] ={
        "BulkGraviton_ZZ_ZlepZhad_M4.5tevW450gev.lhe",
        "BulkGraviton_ZZ_ZlepZhad_M4.5tevW900gev.lhe"};
     */
/*    string namefile[11] ={
        "CosT0.96TanB0.5MH200.lhe",
        "CosT0.96TanB0.5MH300.lhe",
        "CosT0.96TanB0.5MH400.lhe",
        "CosT0.96TanB0.5MH500.lhe",
        "CosT0.96TanB0.5MH600.lhe",
        "CosT0.9TanB1MH200.lhe",
        "CosT0.9TanB1MH300.lhe",
        "CosT0.9TanB1MH400.lhe",
        "CosT0.9TanB1MH500.lhe",
        "CosT0.9TanB1MH600.lhe",
        "SM.lhe"};
 */
    /*
    string namefile[18] ={
        "CosT0.8TanB0.5MH1000.lhe",
        "CosT0.8TanB0.5MH200.lhe",
        "CosT0.8TanB0.5MH300.lhe",
        "CosT0.8TanB0.5MH400.lhe",
        "CosT0.8TanB0.5MH500.lhe",
        "CosT0.8TanB0.5MH600.lhe",
        "CosT0.8TanB1MH1000.lhe",
        "CosT0.8TanB1MH200.lhe",
        "CosT0.8TanB1MH300.lhe",
        "CosT0.8TanB1MH400.lhe",
        "CosT0.8TanB1MH500.lhe",
        "CosT0.8TanB1MH600.lhe",
        "CosT0.96TanB10MH200.lhe",
        "CosT0.96TanB10MH300.lhe",
        "CosT0.96TanB10MH400.lhe",
        "CosT0.96TanB10MH500.lhe",
        "CosT0.96TanB10MH600.lhe",
        "CosT0.9TanB1MH600.lhe"
    };
     */
    string namefile[9] ={
        "L15.0kt1.5cT-3.0cg-0.0816c2g0.3010.lhe",
        "L2.4kt1.25cT2.0cg-0.2560c2g-0.1480.lhe",
        "L-15.0kt2.0cT6.0cg-0.1680c2g-0.5180.lhe",
        "L2.4kt2.25cT2.0cg-0.0616c2g-0.1200.lhe",
        "L10.0kt2.25cT2.0cg-0.2130c2g-0.0893.lhe",
        "L10.0kt1.5cT-1.0cg-0.0956c2g0.1240.lhe",
        "L-15.0kt1.25cT6.0cg-0.0467c2g-0.5150.lhe",
        "L1.0kt0.5cT4.0cg-1.0c2g-0.3780.lhe",
        "L15.0kt0.5cT1.0cg-0.0743c2g-0.0668.lhe"
    };   
    
    //
    string path= "/Users/Xanda/Documents/codes/git/generateHH/clustering/hh_lhe_v1/";
    for(unsigned ifile=0; ifile<9; ifile++){
        //unsigned ifile=0;
        string namefile_in=path;// + "hh_lhe/";
        namefile_in += namefile[ifile];
        /*string namefile_in=path + "Madgraphcg";
         if(ifile==0) namefile_in += "0/MGraviton_260.lhe";
         if(ifile==1) namefile_in += "0/MGraviton_500.lhe";
         if(ifile==2) namefile_in += "1/MGraviton_260.lhe";
         if(ifile==3) namefile_in += "1/MGraviton_500.lhe";
         if(ifile==4) namefile_in += "0_0137/Graviton_Parton/MGraviton_260.lhe";
         if(ifile==5) namefile_in += "0_0137/Graviton_Parton/MGraviton_500.lhe";
         if(ifile==6) namefile_in += "0/MGraviton_260.lhe";
         if(ifile==7) namefile_in += "600.lhe";
         if(ifile==8) namefile_in += "650.lhe";
         if(ifile==9) namefile_in += "700.lhe";
         if(ifile==10) namefile_in += "750.lhe";
         */
//        string namefile_out= path+"ascii/"+ namefile[ifile] + ".ascii4";
          string namefile_out= path+ namefile[ifile] + ".decayed";      
        //    string namefile_in=path + "atEightTeV_processs_patched.lhe";
        //string namefile_out=namefile_in + ".pythia";
        //namefile_in += "test-MR610.lhe";
        cout<<"\n namefile_in = "<<namefile_in<<endl;
        cout<<"\n namefile_out = "<<namefile_out<<endl;
        
        
        // output file
        // we want to store the list of all final state particles
        ofstream out_pythia;
        // Highest precision required for jet clustering
        out_pythia.precision(15);
        // Generator. We here stick with default values, but changes
        // could be inserted with readString or readFile
        // Initialize Les Houches process File run. List initialization information.
        pythia.readString("Beams:frameType = 4");
        // the analysis program
        string sfile = "Beams:LHEF ="+namefile_in;
        pythia.readString(sfile.c_str());
        out_pythia.open(namefile_out.c_str());
        // Allow for possibility of a few faulty processs.
        int nAbort = 10;
        int iAbort = 0;
        // turn of hadronization settings - for testing  
        //  pythia.readString("25:mayDecay = no");
        ////////////////////////////////////////////////////////////////////
        // read decay table
        //pythia.readString("ProcessLevel:resonanceDecays = off"); // do not decay anything
        //pythia.readString("SLHA:readFrom = 2");
        //pythia.readString("SLHA:file = Susy.txt "); // input the decay table
        ////////////////////////////////////////////////////////////////////
        pythia.readString("PartonLevel:all = off"); // Off multiple interactions
        //pythia.readString("PartonLevel:ISR = off"); // Shower on
        //pythia.readString("PartonLevel:FSR = off"); // Shower on
        //pythia.readString("PartonLevel:FSRinResonances  = off"); // Off multiple interactions
        pythia.readString("HadronLevel:all = off"); // Of hadronization
        
        pythia.init();
        
        for (int iprocess = 0; ; ++iprocess) {
           // cout<<"\n iprocess = "<<iprocess<<"\n"<<endl;
            // Generate processs, and check whether generation failed.
            if (!pythia.next()) {
                // If failure because reached end of file then exit process loop.
                if (pythia.info.atEndOfFile()) break;
                // First few failures write off as "acceptable" errors, then quit.
                if (++iAbort < nAbort) continue;
                break;
            }
            //cout<<"hi"<<endl;
            // Acess process record  pythia.process.size()
            //cout<<"Number of particles = "<<pythia.process.size()<<endl;
            vector<int> pID;
            vector<double> px;
            vector<double> py;
            vector<double> pz;
            vector<double> E;
            vector<double> M;
            vector<int> mother;
            vector<int> code;
            // Some checks on the process record
            // Check for example that at least we have two bs and two bbars
            for (int i = 0; i < pythia.process.size(); i++){
                int particle_id = pythia.process[i].id();
                int particle_status = pythia.process[i].status();
                int particle_mother = pythia.process[i].mother1();
                // save only final state particles
                if(particle_id==25){//particle_status>0//(particle_status>0){
                    //cout<<i<<" "<<particle_id<<" "<<particle_mother<<" "<<particle_status<<endl;
                    double ppx= pythia.process[i].px();
                    double ppy= pythia.process[i].py();
                    double ppz= pythia.process[i].pz();
                    double EE= pythia.process[i].e();
                    double MM= pythia.process[i].m();
                    //cout<<px<<" "<<py<<" "<<pz<<" "<<E<<endl;
                    pID.push_back(particle_id);
                    px.push_back(ppx);
                    py.push_back(ppy);
                    pz.push_back(ppz);
                    E.push_back(EE);
                    M.push_back(MM);
                    mother.push_back(particle_mother);
                    code.push_back(particle_id);
                }
            }
            // Save into file
            //out_pythia<<"#"<<endl; // remove to clustering
            //cout<<"Number of final state particles = "<<E.size()<<"\n"<<endl;
            //out_pythia<<E.size()<<endl; // remove to clustering
            for(unsigned i=0;i<E.size();i++){
                //out_pythia<<pID.at(i)<<" "<<px.at(i)<<" "<<py.at(i)<<" "<<pz.at(i)<<" "<<E.at(i)<<" "<<M.at(i)<<endl;// pID.at(i)<<" "<<
                out_pythia<<px.at(i)<<" "<<py.at(i)<<" "<<pz.at(i)<<" "<<E.at(i)<<" "<<M.at(i)<<endl;// for clustering
            }
            
            
            // End of process loop.
        }
        
        out_pythia.close();
        
        // Give statistics. Print histogram.
        pythia.stat(); 
        
        
    } //for unsigned
    
    // Done.
    return 0;
}
