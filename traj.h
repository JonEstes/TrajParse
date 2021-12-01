//#ifdef TRAJECTORY_H
//#define TRAJECTORY_H

#include "frame.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <cassert>
#include <fstream>
//Trajectory object

class Traj{ 

  public:
    //Constructors for trajectories with and without topology.
    Traj(std::string traj_file_name, std::string top_file_name){
      name = traj_file_name;
      Parse_Trajectory(name);
      top = 1;
    }
    Traj(std::string traj_file_name){
      name = traj_file_name;
      Parse_Trajectory(name);
      top = 0;
    }    

 
    void GetTrajInfo(){
      std::cout << "Trajectory contains " << n_frames << " frame(s).\n";
    }

    void GetFrameInfo(int frame_index){
      std::cout << "Frame " << frame_index << " info:\n";
      std::cout << "Number of Particles: " << frames.at(frame_index).GetNatoms() << "\n";
      std::cout << "Box dimensions:\nx length: " << frames.at(frame_index).GetXDim() <<"\ny length: " << frames.at(frame_index).GetYDim() << "\nz length: " << frames.at(frame_index).GetZDim() << "\n";
    }


private:
  std::string name;
  int natoms, top, timestep;
  int n_frames = 0;
  std::vector <Frame> frames;  
  double xbound,ybound,zbound;

  std::ifstream dump_file;
  std::vector<std::string> l;
  std::string line;
  

  void Parse_Trajectory(std::string name){

    std::cout << "Reading in data from file.\n"; 
    dump_file.open(name);
    if(!dump_file.is_open()) {std::cerr<<"Error! "<<name<<" does not exist!\n"<<std::endl; exit(1);}   
    
    Parse_Next_Frame();
    Parse_Next_Frame();
    Parse_Next_Frame();

    }   

  void Parse_Next_Frame(){
    //Initial population from header
    std::getline(dump_file,line);

    assert(!line.compare("ITEM: TIMESTEP"));   

    std::getline(dump_file,line); 
    l = split(line,' ');
    timestep = std::stoi(l[0]);
    
    std::getline(dump_file,line);
    assert(!line.compare("ITEM: NUMBER OF ATOMS"));

    std::getline(dump_file,line);
    l = split(line,' ');
    natoms = std::stoi(l[0]);
    
    std::getline(dump_file,line);
    assert(!line.compare("ITEM: BOX BOUNDS pp pp pp")); 

    std::getline(dump_file,line);
    l = split(line,' ');
    xbound = (std::stod(l[1]) - std::stod(l[0]));   
        
    std::getline(dump_file,line);
    l = split(line,' ');
    ybound = (std::stod(l[1]) - std::stod(l[0]));

    std::getline(dump_file,line);
    l = split(line,' ');
    zbound = (std::stod(l[1]) - std::stod(l[0]));
        
    std::getline(dump_file,line);

    Frame f(natoms,timestep,xbound,ybound,zbound);
    frames.push_back(f);
    n_frames++;
    frames.at(n_frames-1).Enter_Header(line);


    for(int i = 0; i < natoms; i++){
      std::getline(dump_file,line);
      l = split(line,' ');
      frames.at(n_frames-1).Add_Atom(line);
    }
  }    
  
};


//#endif

