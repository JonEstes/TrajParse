#ifndef FRAME_H
#define FRAME_H

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
  this->xdim_ = xdim;
  this->ydim_ = ydim;
  this->zdim_ = zdim;
}
int GetNatoms(){return size;}
double GetXDim(){return xdim_;}
double GetYDim(){return ydim_;}
double GetZDim(){return zdim_;}



int ParseColumnNamesFromHeader(std::string line){
   std::vector<std::string> h = split(line,' ');
   gridsize = h.size()-2;
   h.erase(h.begin(),h.begin()+2);
   bool unscaled = true;
   bool wrapped = true;
   
   x_index_ = Get_Param_Index("x",h);
   if (x_index_ == -1){
      x_index_ = Get_Param_Index("xs",h);
      unscaled = false;
      if (x_index_ == -1){
        x_index_ = Get_Param_Index("xu",h);
        unscaled = true;
        wrapped = false;
        if (x_index_ == -1){
          x_index_ = Get_Param_Index("xsu",h);
          unscaled = false;
          wrapped = false;
        }
        else{
          std::cout << "No x coordinate. Please ensure that your trajectory includes x coordinates.";
          exit(1);
        }
      }
   }
   y_index_ = Get_Param_Index("y",h);
   z_index_ = Get_Param_Index("z",h);


   id_index_ = Get_Param_Index("id",h);
   if (id_index_ == -1){
      std::cout << "No atom id number found. Please ensure that your trajectory includes atom ids.";
      exit(1);


   }
   species_index_ = Get_Param_Index("type",h);
   return gridsize;
}

int Eval_Header(std::string line){
  std::vector<std::string> h = split(line,' ');
  gridsize = h.size()-2;
  h.erase(h.begin(),h.begin()+2);
  



  return gridsize;
}




void Add_Atom(std::string line){
  std::vector<std::string> l = split(line,' ');
  id_numbers.at(atom_iterator_) = stoi(l.at(id_index_));
  if (species_index_ != -1){
    atom_types.at(atom_iterator_) = l.at(species_index_);
  }
  coords.at(0).at(atom_iterator_) = stod(l.at(x_index_));
  coords.at(1).at(atom_iterator_) = stod(l.at(y_index_));
  coords.at(2).at(atom_iterator_) = stod(l.at(z_index_));
 
  atom_iterator_++;
}

void Print_Coords(){
  for (int i = 0; i < size; i++){
    std::cout << coords.at(0).at(i) << " " << coords.at(1).at(i) << " " << coords.at(2).at(i) << "\n";
  }
}

int Get_Param_Index(std::string param, std::vector<std::string> atom){
  int index = -1;
  for(int i = 0; i < atom.size(); i++){
    if (!atom.at(i).compare(param)){
      index = i;
      break;
    }
  }
  return index;
}

private:
int size, timestep, gridsize,x_index_,y_index_,z_index_,id_index_,species_index_;
double xdim_, ydim_, zdim_;
int atom_iterator_ = 0;
std::vector<std::string> atom_params;
std::vector<std::vector<double>> configuration;
std::vector<std::vector<double>> coords;
std::vector<std::string> atom_types;
std::vector<int> id_numbers;


};

#endif


