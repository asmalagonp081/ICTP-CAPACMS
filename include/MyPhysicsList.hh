// ----- ICTP-PROJECT ----
// Angela Sofia Malagón Palomino
// Physics List

#ifndef MYPHYSICSLIST_HH
#define MYPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class MyPhysicsList : public G4VUserPhysicsList
{
public:
  MyPhysicsList();
  ~MyPhysicsList();

  // Métodos 
  virtual void ConstructParticle() override;
  virtual void ConstructProcess() override;
  
};

#endif

