// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Mundo --
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

# include "G4VUserDetectorConstruction.hh" // Definido por el usuario
# include "G4LogicalVolume.hh" // Volumen lógico

class G4VPhysicalVolume; // Volumen físico
class G4LogicalVolume; // Volumen lógico

class DetectorConstruction : public G4VUserDetectorConstruction 
{
    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();

        virtual G4VPhysicalVolume* Construct(); // Construcción de la geometría

    private:
        // Defino los volumenes lógicos como miembros de la clase
        G4LogicalVolume* logicWorld;
        G4LogicalVolume* logicLayer1;
        G4LogicalVolume* logicLayer2;
        G4LogicalVolume* logicScoringPlane; // Detector de fluencia
    
};

#endif // DetectorConstruction_h