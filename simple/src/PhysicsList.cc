// SIMULACIÓN DE ATENUACIÓN DE RAYOS GAMMA USANDO G4 Y MULASSIS

#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"

PhysicsList::PhysicsList() 
  : G4VModularPhysicsList(){
  
  SetVerboseLevel(1);

  // Standard EM Physics
  RegisterPhysics(new G4EmStandardPhysics());
  
}

PhysicsList::~PhysicsList()
{ }

void PhysicsList::SetCuts()
{
  // The method SetCuts() is mandatory in the interface. Here, one just use 
  // the default SetCuts() provided by the base class.

  G4VUserPhysicsList::SetCuts();
}  



