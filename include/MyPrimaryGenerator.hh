// ----- ICTP-PROJECT ----
// Angela Sofia Malagón Palomino
// Primary Generator Action

#ifndef MYPRIMARYGENERATORACTION_HH
#define MYPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
    MyPrimaryGeneratorAction();    // Constructor
    ~MyPrimaryGeneratorAction();   // Destructor

    // Este es el método más importante: define qué pasa en cada disparo
    virtual void GeneratePrimaries(G4Event*) override;

private:
    G4ParticleGun* fParticleGun; // El "cañón" de partículas
};
#endif // MYPRIMARYGENERATORACTION_HH