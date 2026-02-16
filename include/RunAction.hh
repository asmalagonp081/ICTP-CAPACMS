// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- G4Run --
#ifndef UserRunAction_h
#define UserRunAction_h 1

# include "G4Run.hh" // Inclusión de G4Run
# include "G4RunManager.hh" // Inclusion de la otra clase
# include "G4UserRunAction.hh" // Definido por el usuario

UserRunAction::UserRunAction() {}
UserRunAction::~UserRunAction() {}

void UserRunAction::BeginOfRunAction(const G4Run*)
{
    // Parametros inciales para el run
}
void UserRunAction::EndOfRunAction(const G4Run*)
{
    // Parametros finales para el run
    // Se cierran archivos de adquisicion de datos, o algo así
}
