// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- El que mira las partículas en cada paso --
#include "G4Step.hh"

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // 1. Obtenemos el punto de inicio del paso
    G4StepPoint* prePoint = step->GetPreStepPoint();
    
    // 2. Obtenemos el volumen físico donde está ese punto
    G4VPhysicalVolume* currentVolume = prePoint->GetTouchableHandle()->GetVolume();

    // 3. Lógica de conteo: ¿Estamos entrando al plano de scoring del Plomo?
    if (currentVolume->GetName() == "ScoringPb") {
        
        // Verificamos si es el primer paso dentro del volumen
        if (prePoint->GetStepStatus() == fGeomBoundary) {
            auto analysisManager = G4AnalysisManager::Instance();
            
            // Registramos que una partícula cruzó (Columna 1 del Ntuple)
            analysisManager->FillNtupleIColumn(1, 1); 
            
            // También podemos registrar la energía que lleva en ese instante
            G4double energy = prePoint->GetKineticEnergy();
            analysisManager->FillNtupleDColumn(0, energy);
        }
    }
}