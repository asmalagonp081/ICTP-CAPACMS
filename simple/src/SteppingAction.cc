#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

SteppingAction::SteppingAction()
: fTransmitted(0)
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

  // --- Filtro de Haz Estrecho ---
  // Si el fotón primario interactúa (pierde energía), lo eliminamos de inmediato.
  // Esto garantiza que solo los fotones "puros" puedan llegar al final.
  if(std::abs(track->GetKineticEnergy() - track->GetVertexKineticEnergy()) > 1*eV) {
      track->SetTrackStatus(fStopAndKill);
      return;
  }

  auto prePoint  = step->GetPreStepPoint();
  auto postPoint = step->GetPostStepPoint();

  if(!prePoint || !postPoint) return;
  auto preVol  = prePoint->GetTouchableHandle()->GetVolume();
  auto postVol = postPoint->GetTouchableHandle()->GetVolume();

  if(!preVol) return;

  // --- Detección en la salida de la última capa (Concreto - Box3) ---
  // El fotón solo llega aquí si pasó por el plomo sin interactuar.
  if(preVol->GetName() == "Box3")
    {
      if(postVol && postVol->GetName() != "Box3")
        {
          fTransmitted++;

          // Guardar datos en análisis
          auto analysisManager = G4AnalysisManager::Instance();
          if(analysisManager) {
            G4double E = track->GetKineticEnergy();
            // Llenar histograma de energía
            analysisManager->FillH1(0, E);  // H1 "Egamma"

            // Llenar ntuple con datos detallados
            analysisManager->FillNtupleDColumn(0, E);  // Energía
            analysisManager->FillNtupleDColumn(1, track->GetPosition().z());  // Posición Z
            analysisManager->FillNtupleIColumn(2, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());  // EventID
            analysisManager->AddNtupleRow();
          }

          // Matamos la partícula después de contarla para evitar doble conteo
          track->SetTrackStatus(fStopAndKill);
        }
    }
}
