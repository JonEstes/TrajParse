//#ifndef FRAME_H
//#define FRAME_H

#include <vector>
#include <string.h>
#include "utils.h"
//frame object within a trajectory

class Frame{ 

public:
Frame(int natoms, int time, double xdim, double ydim, double zdim){
  size = natoms;
  coords.resize(3,std::vector<double>(size));
  atom_types.resize(size);
  id_numbers.resize(size);
  time = timestep;
  this->xdim = xdim;
  this->ydim = ydim;
  this->zdim = zdim;
}
int GetNatoms(){return size;}
double GetXDim(){return xdim;}
double GetYDim(){return ydim;}
double GetZDim(){return zdim;}



int Enter_Header(std::string line){
   h = split(line,' ');
   gridsize = h.size()-2;
   h.erase(h.begin(),h.begin()+2);
   x_index = Get_Param_Index("x");
   y_index = Get_Param_Index("y");
   z_index = Get_Param_Index("z");
   id_index = Get_Param_Index("id");
   species_index = Get_Param_Index("type");
   return gridsize;
}



void Add_Atom(std::string line){
  l = split(line,' ');
  id_numbers.at(atom_iterator) = stoi(l.at(id_index));
  atom_types.at(atom_iterator) = l.at(species_index);
  coords.at(0).at(atom_iterator) = stod(l.at(x_index));
  coords.at(1).at(atom_iterator) = stod(l.at(y_index));
  coords.at(2).at(atom_iterator) = stod(l.at(z_index));
 
  atom_iterator++;
}

void Print_Coords(){
  for (int i = 0; i < size; i++){
    std::cout << coords.at(0).at(i) << " " << coords.at(1).at(i) << " " << coords.at(2).at(i) << "\n";
  }
}

int Get_Param_Index(std::string param){
  int x = -1;
  for(int i = 0; i < h.size(); i++){
    if (!h.at(i).compare(param)){
      x = i;
      break;
    }
  }
  return x;
}

private:
int size, timestep, gridsize,x_index,y_index,z_index,id_index,species_index;
double xdim, ydim, zdim;
std::vector<std::string> h;
std::vector<std::string> l;
int atom_iterator = 0;
std::vector<std::string> atom_params;
std::vector<std::vector<double>> configuration;
std::vector<std::vector<double>> coords;
std::vector<std::string> atom_types;
std::vector<int> id_numbers;


};

//#endif


