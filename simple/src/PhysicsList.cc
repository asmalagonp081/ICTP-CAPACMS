//Define la física a usar en la simulación

#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList() 
  : G4VModularPhysicsList(){
  
  SetVerboseLevel(1);

  // Standard EM Physics
  RegisterPhysics(new G4EmStandardPhysics());
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void PhysicsList::SetCuts()
{
  // The method SetCuts() is mandatory in the interface. Here, one just use 
  // the default SetCuts() provided by the base class.

  G4VUserPhysicsList::SetCuts();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

