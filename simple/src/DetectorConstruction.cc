//Construcción del target, detector

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVDivision.hh"
#include "G4SubtractionSolid.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction(),
    fCheckOverlaps(true)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Llamado a la base de datos del NIST
  G4NistManager* nist = G4NistManager::Instance();

  //Definición del "vacío"
  G4double presion, temperatura, densidad;
  densidad     = universe_mean_density;    //from PhysicalConstants.h
  presion    = 3.e-18*pascal;
  temperatura = 2.73*kelvin;
  G4Material* Vacuum   = new G4Material("Vacuum",
                                        1., 1.01*g/mole, densidad,
                                        kStateGas,temperatura,presion);

  

  //Definición del material 
  G4Material* boxmaterial = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* boxmaterial2 = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4Material* boxmaterial3 = nist->FindOrBuildMaterial("G4_Galactic");

  
  // World ()
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  G4double world_sizeXY = 2.0*meter;
  G4double world_sizeZ  = 2.0*meter;
  
  //Solid volume
  G4Box* solidWorld = new G4Box("World",
				0.5*world_sizeXY,
				0.5*world_sizeXY,
				0.5*world_sizeZ); //its size
  
  //Logical volume
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        Vacuum,         //its material
                        "World");            //its name
  
  //Physical volume
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps 


  G4double boxHLX   = 0.005*cm;//0.25*m;
  G4double boxHLY   = 0.005*cm;//0.25*m;
  G4double boxHLZ   = 0.005*mm;//0.10*cm;
  G4double box2HLZ  = 0.1*mm;//0.20*cm;
  G4double box3HLZ  = 0.0025*cm;//0.20*cm;
  
  // Box volume - Plomo
  G4Box* solidBox = new G4Box("Box", boxHLX, boxHLY, boxHLZ);
  G4LogicalVolume *logicBox = new G4LogicalVolume(solidBox, boxmaterial,"Box");
  new G4PVPlacement(0, G4ThreeVector(), logicBox, "Box", logicWorld, false, 0, fCheckOverlaps); 

  // Box volume2 - Vacio
  G4Box* solidBox2 = new G4Box("Box2", boxHLX, boxHLY, boxHLZ);
  G4LogicalVolume *logicBox2 = new G4LogicalVolume(solidBox2, boxmaterial3,"Box2");
  new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, boxHLZ + boxHLZ), logicBox2, "Box2", logicWorld, false, 0, fCheckOverlaps); 

  // Box volume3 - Concreto
  G4Box* solidBox3 = new G4Box("Box3", box3HLX, box3HLY, box3HLZ);
  G4LogicalVolume *logicBox3 = new G4LogicalVolume(solidBox3, boxmaterial2,"Box3");
  new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, boxHLZ + boxHLZ + box3HLZ), logicBox3, "Box3", logicWorld, false, 0, fCheckOverlaps); 

  // Box volume4 - Vacio
  G4Box* solidBox4 = new G4Box("Box4", box3HLX, box3HLY, box3HLZ);
  G4LogicalVolume *logicBox4 = new G4LogicalVolume(solidBox4, boxmaterial3,"Box4");
  new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, boxHLZ + boxHLZ + box3HLZ + box3HLZ), logicBox4, "Box4", logicWorld, false, 0, fCheckOverlaps); 

  
  //retorna objeto apuntador a la clase G4VPhysicalVolume
  return physWorld; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

