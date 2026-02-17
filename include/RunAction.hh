// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- G4Run --
#ifndef UserRunAction_h
#define UserRunAction_h 1

# include "G4VUserRunAction.hh" // Definido por el usuario

class G4Run; // Para usar G4Run

class UserRunAction : public G4VUserRunAction
{
    public:
        UserRunAction();
        virtual ~UserRunAction();

        virtual void BeginOfRunAction(const G4Run*); // Acción al inicio del run
        virtual void EndOfRunAction(const G4Run*); // Acción al final del run

};

#endif // UserRunAction_h
