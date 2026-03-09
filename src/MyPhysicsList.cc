// ----- ICTP-PROJECT ----
// Angela Sofia Malagón Palomino
// Physics List
#include "MyPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"

MyPhysicsList::MyPhysicsList() : G4VUserPhysicsList() {
    // Definimos qué tan precisa será la simulación (Cuts)
    defaultCutValue = 1.0*mm; 
}

MyPhysicsList::~MyPhysicsList() {}

void MyPhysicsList::ConstructParticle() {
    G4Gamma::GammaDefinition();
    G4Electron::ElectronDefinition();
}

void MyPhysicsList::ConstructProcess() {
    AddTransportation(); // Permite que las partículas se muevan
    
    // Aquí registramos el constructor EM estándar
    G4VPhysicsConstructor* emPhysics = new G4EmStandardPhysics();
    emPhysics->ConstructProcess();
}