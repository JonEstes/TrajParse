#include "traj.h"

//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <string>
using namespace std;

int main(){

Trajectory traj1("dump.coords.lammpstrj","test");

traj1.GetFrameInfo(0);
traj1.GetTrajInfo();

Frame f = traj1.at(0);

f.PrintCoords();

//traj1.PrintAtomInfoInFrame(0);
//traj1.PrintAtomInfoInFrame(2);
}


