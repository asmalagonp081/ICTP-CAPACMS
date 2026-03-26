#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GenericMessenger.hh"


class G4ParticleGun; // Es reduntante ya que se importó el header, pero se deja para evitar errores de compilación en caso de que se comente la línea de importación.

class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();  // Constructor   
  virtual ~PrimaryGeneratorAction(); // Destructor

  virtual void GeneratePrimaries(G4Event*); // Método que le dice a la pistola que dispare        
  
  // Energías
  void SetParticleEnergy(G4double val);
private: 
  G4ParticleGun*  fParticleGun;

  // Energía
  G4double fParticleEnergy;
  
  // Messenger
  G4GenericMessenger* fMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


