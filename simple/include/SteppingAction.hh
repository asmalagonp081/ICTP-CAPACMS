#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SteppingAction : public G4UserSteppingAction
{
public:

  SteppingAction(G4double E0);
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step*);

  G4int GetTransmitted() const { return fTransmitted; }

private:

  G4double fE0;

  G4int fTransmitted;   // contador de fotones buenos
};

#endif

