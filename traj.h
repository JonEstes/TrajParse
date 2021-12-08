#ifndef TRAJECTORY_H
#define TRAJECTORY_H

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

class Trajectory{ 

  public:
    //Constructors for trajectories with and without topology.
    Trajectory(std::string traj_file_name, std::string topology_file_name){
      Parse_Trajectory(traj_file_name);
      topology_ = true;
    }
    Trajectory(std::string traj_file_name){
      Parse_Trajectory(traj_file_name);
      topology_ = false;
    }    

 
    void GetTrajInfo(){
      std::cout << "Trajectory contains " << n_frames << " frame(s).\n";
    }

    void GetFrameInfo(int frame_index){
      std::cout << "Frame " << frame_index << " info:\n";
      std::cout << "Number of Particles: " << frames.at(frame_index).GetNatoms() << "\n";
      std::cout << "Box dimensions:\nx length: " << frames.at(frame_index).GetXDim() <<"\ny length: " << frames.at(frame_index).GetYDim() << "\nz length: " << frames.at(frame_index).GetZDim() << "\n";
    }

    Frame& operator[](int index){
      if (index >= n_frames){
        std::cout << "Frame out of bounds. Exiting\n";
        exit(1);
      }else{
        return frames[index];
      }
    }
    Frame& at(int index){return operator[](index);}    


private:
  int natoms_, timestep;
  bool topology_;
  int n_frames = 0;
  std::vector <Frame> frames;  
  double xbound,ybound,zbound;

  std::ifstream dump_file;
  

  void Parse_Trajectory(std::string name){
    std::string line;
    std::cout << "Reading in data from file.\n"; 
    dump_file.open(name);
    if(!dump_file.is_open()) {std::cerr<<"Error! "<<name<<" does not exist!\n"<<std::endl; exit(1);}   
   

    std::getline(dump_file,line);
    while(1){ 
      line = Parse_Next_Frame(line);
      if (!line.compare("ITEM: TIMESTEP")){break;}
    }
  }   

  std::string Parse_Next_Frame(std::string line){
    //Initial population from header
    //std::getline(dump_file,line);
    std::vector<std::string> l;
    assert(!line.compare("ITEM: TIMESTEP"));   

    std::getline(dump_file,line); 
    l = split(line,' ');
    timestep = std::stoi(l[0]);
    
    std::getline(dump_file,line);
    assert(!line.compare("ITEM: NUMBER OF ATOMS"));

    std::getline(dump_file,line);
    l = split(line,' ');
    natoms_ = std::stoi(l[0]);
    
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

    Frame f(natoms_,timestep,xbound,ybound,zbound);
    frames.push_back(f);
    n_frames++;
    frames.at(n_frames-1).ParseColumnNamesFromHeader(line);


    for(int i = 0; i < natoms_; i++){
      std::getline(dump_file,line);
      l = split(line,' ');
      frames.at(n_frames-1).Add_Atom(line);
    }
    std::getline(dump_file,line);
    return line;
  }    
  
};


#endif

