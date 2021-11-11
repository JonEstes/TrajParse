#include "frame.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <cassert>
//Trajectory object

class Traj{ 

  public:
    Traj(std::string filename){
      name = filename;
      Populate(name);
    }
    
    void GetTrajInfo(){
      std::cout << "Trajectory contains " << n_frames << " frame(s).\n";
    }

    void GetFrameInfo(int frame_index){
      std::cout << "Frame " << frame_index << " info:\n";
      std::cout << "Number of Particles: " << frames.at(frame_index).GetNatoms() << "\n";
      std::cout << "Box dimensions:\nx length: " << frames.at(frame_index).GetXDim() <<"\ny length: " << frames.at(frame_index).GetYDim() << "\nz length: " << frames.at(frame_index).GetZDim() << "\n";
    }

    void PrintAtomInfoInFrame(int frame_index){
    frames.at(frame_index).PrintAtoms(); 
      }

    void PrintAtom(int frame_index, int atom_index){
      frames.at(frame_index).PrintAtom(atom_index);
    }

private:
  std::string name;
  int natoms;
  int n_frames = 0;
  std::vector <Frame> frames;  
  double xbound,ybound,zbound;
  
  void Populate(std::string name){
    std::string line;
    int timestep;
    std::vector<std::string> l;

    std::cout << "Reading in data from file.\n"; 
    std::ifstream dump_file;
    dump_file.open(name);
    if(!dump_file.is_open()) {std::cerr<<"Error! "<<name<<" does not exist!\n"<<std::endl; exit(1);}    
    
    //Initial population from header
    std::getline(dump_file,line);
    while (!line.compare("ITEM: TIMESTEP")){
    assert(!line.compare("ITEM: TIMESTEP"));   

    std::getline(dump_file,line); 
    l = ofts::split(line,' ');
    timestep = std::stoi(l[0]);
    //std::cout<< "Timestep = " << timestep << ".\n";
    
    std::getline(dump_file,line);
    assert(!line.compare("ITEM: NUMBER OF ATOMS"));

    std::getline(dump_file,line);
    l = ofts::split(line,' ');
    natoms = std::stoi(l[0]);
    //std::cout<< "Number of Atoms = " << natoms << ".\n";
    
    std::getline(dump_file,line);
    assert(!line.compare("ITEM: BOX BOUNDS pp pp pp")); 

    std::getline(dump_file,line);
    l = ofts::split(line,' ');
    xbound = (std::stod(l[1]) - std::stod(l[0]));   
        
    std::getline(dump_file,line);
    l = ofts::split(line,' ');
    ybound = (std::stod(l[1]) - std::stod(l[0]));

    std::getline(dump_file,line);
    l = ofts::split(line,' ');
    zbound = (std::stod(l[1]) - std::stod(l[0]));
    
    //std::cout << "Box dimensions: " << xbound << ", " << ybound << ", " << zbound << "\n";
        
    std::getline(dump_file,line);
    assert(!line.compare("ITEM: ATOMS id type x y z"));

    Frame f(natoms,timestep,xbound,ybound,zbound);

    frames.push_back(f);
    n_frames++;
    for(int i = 0; i < natoms; i++){
      std::getline(dump_file,line);
      l = ofts::split(line,' ');
      frames.at(n_frames-1).Add_Atom(std::stoi(l[0]),std::stoi(l[1]), std::stod(l[2]),std::stod(l[3]),std::stod(l[4]));
      //std::cout << "Added atom " << i+1 << "\n";
    }
      std::getline(dump_file,line);
    }
    

  }


};













