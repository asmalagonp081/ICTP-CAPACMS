#include "MyPrimaryGenerator.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1); // Dispara 1 partícula por evento

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    fParticleGun->SetParticleDefinition(particleTable->FindParticle("gamma"));
    
    // Dirección fija en el eje Z
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0*MeV);
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() {
    delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Posición de la fuente (10 cm antes del origen)
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -10*cm));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}