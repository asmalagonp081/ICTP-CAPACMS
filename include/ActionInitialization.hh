// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Main function --

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh" // Definido por el usuario

class ActionInitialization : public G4VUserActionInitialization
{   
    public:
        ActionInitialization();
        virtual ~ActionInitialization();

        virtual void Build() const; // Método para construir las acciones
};

#endif // ActionInitialization_h