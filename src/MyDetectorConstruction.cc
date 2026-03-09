#include "MyDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

MyDetectorConstruction::MyDetectorConstruction() : G4VUserDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    // 1. Definición de Materiales 🧪
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* lead_mat = nist->FindOrBuildMaterial("G4_Pb"); // Plomo para el blindaje

    // 2. El Mundo (World) 🌎
    // Es el volumen contenedor. Todo debe estar dentro de él.
    G4double world_size = 0.5 * m;
    G4Box* solidWorld = new G4Box("World", world_size, world_size, world_size);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // 3. El Blindaje (Shield) 🛡️
    // Vamos a crear una placa de 1 cm de espesor (Z)
    G4double shield_thickness = 0.5 * cm; // Semiespesor (Geant4 usa la mitad del ancho para G4Box)
    G4Box* solidShield = new G4Box("Shield", 10.*cm, 10.*cm, shield_thickness);
    G4LogicalVolume* logicShield = new G4LogicalVolume(solidShield, lead_mat, "Shield");

    // Lo colocamos en el origen (0,0,0)
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicShield, "Shield", logicWorld, false, 0);

    return physWorld;
}