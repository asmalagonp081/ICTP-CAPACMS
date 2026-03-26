//Define el haz incidente

#include "PrimaryGeneratorAction.hh"

//#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
//#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),
    fParticleGun(nullptr),
    fParticleEnergy(1.0*MeV)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  
  // -- Messenger --
  fMessenger = new G4GenericMessenger(this, "/simple/gun/", "Gun control");
  fMessenger->DeclareMethod("energy",
                            &PrimaryGeneratorAction::SetParticleEnergy,
                            "Set the energy of the particle");

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-0.5*meter));
  fParticleGun->SetParticleEnergy(fParticleEnergy);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  
}

//....oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fMessenger;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //Create the vertex of the primary particle passing it to the G4Event pointer
  fParticleGun->GeneratePrimaryVertex(anEvent); 
}

void PrimaryGeneratorAction::SetParticleEnergy(G4double val)
{
  fParticleEnergy = val;
  if(fParticleGun) fParticleGun->SetParticleEnergy(fParticleEnergy);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
