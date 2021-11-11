//atom object within a frame

//constructor
class Atom{ 

public:
Atom(int atom_id, int species, float x,float y,float z){
  xcoord = x;
  ycoord = y;
  zcoord = z;
  atom_species = species;
  this->atom_id = atom_id;
}


double GetXCoord(){return xcoord;}
double GetYCoord(){return ycoord;}
double GetZCoord(){return zcoord;}
int GetSpecies(){return atom_species;}
int GetLammpsID(){return atom_id;}

private:
double xcoord,ycoord,zcoord;
int atom_species,atom_id;

};
