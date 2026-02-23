// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Fuente de Partículas --

#include "PrimaryGeneratorAction.hh" // Agrego el encabezado
#include "G4LogicalVolumeStore.hh" // Para acceder a los volúmenes lógicos
#include "G4LogicalVolume.hh" // Para usar G4LogicalVolume
#include "G4Box.hh" // Para crear cajas
#include "G4ParticleTable.hh" // Para acceder a la tabla de partículas
#include "G4ParticleDefinition.hh" // Para usar G4ParticleDefinition
#include "G4SystemOfUnits.hh" // Para usar unidades de medida

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
 {
    fParticleGun = new G4ParticleGun(1); // 1 partícula por evento

    // Temporal (por defecto)
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");

    fParticleGun->SetParticleDefinition(particle); // Defino el tipo de partícula (gamma)
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.)); // Dispara en el eje z
    fParticleGun->SetParticleEnergy(1.0*MeV); // Energía inicial
 }

 PrimaryGeneratorAction::~PrimaryGeneratorAction()
 {
    delete fParticleGun; // Libero memoria
 }

 void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
    {
        // Obtengo el volumen lógico del mundo para colocar la fuente en su centro
        G4LogicalVolume* logicWorld = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
        if (logicWorld) {
            G4ThreeVector pos = logicWorld->GetSolid()->GetExtent() / 2.0; // Posición en el centro del mundo
            fParticleGun->SetParticlePosition(pos); // Coloco la fuente en el centro del mundo
        } else {
            G4Exception("PrimaryGeneratorAction::GeneratePrimaries()", "MyCode0001", JustWarning, "No se encontró el volumen lógico 'World'. La fuente se colocará en el origen.");
            fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -5.*cm)); // Coloco la fuente en el origen
        }
        fParticleGun->GeneratePrimaryVertex(anEvent); // Genero la partícula
    }