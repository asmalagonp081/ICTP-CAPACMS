// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Mundo --
# include "DetectorConstruction.hh" // Llamamos a la cabecera definida

#include "G4RunManager.hh" // Controla el flujo del programa
#include "G4NistManager.hh" // Para obtener datos de materiales
#include "G4Box.hh" // Para definir la geometría de la caja
#include "G4LogicalVolume.hh" // Para definir el volumen lógico
#include "G4PVPlacement.hh" // Para colocar el volumen físico
#include "G4SystemOfUnits.hh" // Para usar unidades de medida

// -- Instancio la clase --
DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction() // Constructor de la clase
{}

DetectorConstruction::~DetectorConstruction() 
{} // Destructor de la clase

// -- Método para la geometría --
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance(); // Instancia del gestor de materiales
    // -- Material del mundo --
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR"); // AIRE

    // -- Materiales de la capa: Pb & Concreto --
    G4Material* mat_Pb = nist->FindOrBuildMaterial("G4_Pb"); // PLOMO
    G4Material* mat_Concrete = nist->FindOrBuildMaterial("G4_CONCRETE"); // CONCRETO

    // -- Materiales de la capa: Polietileno & Aluminio --
    G4Material* mat_Poly = nist->FindOrBuildMaterial("G4_POLYETHYLENE"); // POLIETILENO
    G4Material* mat_Al = nist->FindOrBuildMaterial("G4_Al"); // ALUMINIO

    // -- Geometría del mundo --
    G4double world_size = 20*cm; // Tamaño del mundo
    G4Box* solidWorld = new G4Box("World", 0.5*world_size, 0.5*world_size, 0.5*world_size); // Caja del mundo
    logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World"); // Volumen lógico del mundo
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0); // Volumen físico del mundo

    // -- Geometría multicapa --
    G4double thickness1 = 2.0*cm; 
    G4double thickness2 = 3.0*cm;
    G4double sizeXY    = 8.0*cm;

    // -- Capa 1: Pb --
    G4Box* solidPb = new G4Box("PbLayer", sizeXY/2, sixeXY/2, thickness1/2); // Caja de la capa de Pb
    logicPb = new G4LogicalVolume(solidPb, mat_Pb, "PbLayer"); // Volumen lógico de la capa de Pb
    new G4PVPlacement(0, G4ThreeVector(0, G4ThreeVector(0, 0, thickness1/2), logicPb, "PbLayer", logicWorld, false, 0)); 

    // -- Capa 2: Concreto --
    G4Box* solidConc = new G4Box("ConcLayer", sizeXY/2, sizeXY/2, thickness2/2); // Caja de la capa de concreto
    logicConc = new G4LogicalVolume(solidConc, mat_Concrete, "ConcLayer"); // Volumen lógico de la capa de concreto
    new G4PVPlacement(0, G4ThreeVector(0, G4ThreeVector(0, 0, thickness1+
}