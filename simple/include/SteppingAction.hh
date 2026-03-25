#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SteppingAction : public G4UserSteppingAction
{
public:

  SteppingAction();
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step*);

  G4int GetTransmitted() const { return fTransmitted; }

private:

  G4int fTransmitted;   // contador de fotones buenos
};

#endif
