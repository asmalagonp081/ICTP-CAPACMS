#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

SteppingAction::SteppingAction(G4double E0)
: fE0(E0),
  fTransmitted(0)
{}

SteppingAction::~SteppingAction()
{
   G4cout << "-----------------------------------" << G4endl;
   G4cout << "Transmitted uncollided gammas: "
          << fTransmitted << G4endl;
   G4cout << "-----------------------------------" << G4endl;
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  auto track = step->GetTrack();

  // solo gammas
  if(track->GetDefinition() != G4Gamma::Gamma())
      return;

  // solo primarios
  if(track->GetParentID() != 0)
      return;

  auto prePoint  = step->GetPreStepPoint();
  auto postPoint = step->GetPostStepPoint();

  if(!prePoint || !postPoint) return;
  auto preVol  = prePoint->GetTouchableHandle()->GetVolume();
  auto postVol = postPoint->GetTouchableHandle()->GetVolume();
  
  if(!preVol) return;

 // detectar salida del plomo
  if(preVol->GetName() == "Box")
    {
      if(postVol && postVol->GetName() != "Box")
	{
          G4double E = track->GetKineticEnergy();
	  
          if(std::abs(E - fE0) < 1*eV)
	    {
              fTransmitted++;
	      
              track->SetTrackStatus(fStopAndKill);
	    }
	}
    }
}
  //auto preVol  = prePoint->GetTouchableHandle()->GetVolume();
  //auto postVol = postPoint->GetTouchableHandle()->GetVolume();
  //  auto preVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
  //  auto postVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName();

  // fotón sale del plomo
  //if(preVolume == "Box" && postVolume != "Box")
  //{
//  G4double E = track->GetKineticEnergy();

//    if(std::abs(E - fE0) < 1*eV)
//    {
//        fTransmitted++;

//        track->SetTrackStatus(fStopAndKill);
//    }
//}
//}
