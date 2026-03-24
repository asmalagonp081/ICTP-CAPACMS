#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
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

              // Guardar datos en análisis
              auto analysisManager = G4AnalysisManager::Instance();
              if(analysisManager) {
                // Llenar histograma de energía
                analysisManager->FillH1(0, E);  // H1 "Egamma"

                // Llenar ntuple con datos detallados
                analysisManager->FillNtupleDColumn(0, E);  // Energía
                analysisManager->FillNtupleDColumn(1, track->GetPosition().z());  // Posición Z
                analysisManager->FillNtupleIColumn(2, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());  // EventID
                analysisManager->AddNtupleRow();
              }

              track->SetTrackStatus(fStopAndKill);
	    }
	}
    }
}
