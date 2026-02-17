// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Fuente de fotones --
#ifndef PrimaryGenerator_h
#define PrimaryGenerator_h 1

#include "G4VUserPrimaryGeneratorAction.hh" // Definido por el usuario
#include "G4ParticleGun.hh" // Para generar partículas
#include "globals.hh" // Para usar unidades de medida

class G4Event;

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction 
{
    public:
        PrimaryGenerator();
        virtual ~PrimaryGenerator();

        virtual void GeneratePrimaries(G4Event*); // Método para generar partículas primarias

    private:
        G4ParticleGun* fParticleGun; // Cañón de particulas
};

#endif // PrimaryGenerator_h
