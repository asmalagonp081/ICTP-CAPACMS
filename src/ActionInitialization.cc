// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Build --
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

// Este método es para simulaciones que usan muchos núcleos del procesador (Multi-threading)
void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}

// Este método es donde definimos qué hace cada "hilo" de trabajo
void ActionInitialization::Build() const
{
  // 1. El que dispara: PrimaryGeneratorAction
  SetUserAction(new PrimaryGeneratorAction);

  // 2. El que anota el resumen: RunAction
  SetUserAction(new RunAction);
  
  // 3. El que vigila cada paso: SteppingAction (lo crearemos después)
  SetUserAction(new SteppingAction); 
}