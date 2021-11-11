#include "atom.h"
#include <vector>
//frame object within a trajectory

class Frame{ 

public:
Frame(int natoms, int time, double xdim, double ydim, double zdim){
  size = natoms;
  time = timestep;
  this->xdim = xdim;
  this->ydim = ydim;
  this->zdim = zdim;
}
int GetNatoms(){return size;}
double GetXDim(){return xdim;}
double GetYDim(){return ydim;}
double GetZDim(){return zdim;}



void Add_Atom(int id, int species, double x, double y, double z){
  Atom a(id, species,x,y,z);
  atoms.push_back(a);
}

void PrintAtoms(){

std::cout << "Atom_id Species x_coord y_coord z_coord\n";
  for (int i = 0; i < size; i++){
    PrintAtom(i);
  } 
}

void PrintAtom(int atom_index){
  if( atom_index > size-1){
    std::cout << "ERROR: Atom_index requested is greater than number of atoms in frame.\n";
  }else{
  std::cout << "Atom_id Species x_coord y_coord z_coord\n";
  std::cout << atoms.at(atom_index).GetLammpsID() << " " << atoms.at(atom_index).GetSpecies() << " " << atoms.at(atom_index).GetXCoord() << " " << atoms.at(atom_index).GetYCoord() << " " << atoms.at(atom_index).GetZCoord()  <<"\n";
  }
}


private:
int size, timestep;
double xdim, ydim, zdim;
std::vector <Atom> atoms;


};
