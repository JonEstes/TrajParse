#include "traj.h"

//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <string>
using namespace std;

int main(){

Traj traj1("dump.coords.lammpstrj","test");

traj1.GetFrameInfo(0);
traj1.GetTrajInfo();
//traj1.PrintAtomInfoInFrame(0);
//traj1.PrintAtomInfoInFrame(2);
}


