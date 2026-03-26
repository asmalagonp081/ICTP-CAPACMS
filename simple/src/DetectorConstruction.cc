//Construcción del target, detector

// -- Librerias --
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

// -- Constructor --
DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction(),
    fCheckOverlaps(true),
    fThickness(0.005*cm),
    aThickness(0.005*cm)
{
  // -- Messenger --
  // Permite hacer el barrido de espesores desde el macro
  fMessenger = new G4GenericMessenger(this, "/simple/det/", "Detector control");

  fMessenger->DeclareMethod("thickness",
                            &DetectorConstruction::SetThickness,
                            "Set the thickness of Pb and gap");

  fMessenger->DeclareMethod("aThickness",
                            &DetectorConstruction::SetAThickness,
                            "Set the thickness of Concreto and second gap");

}

// -- Destructor --
DetectorConstruction::~DetectorConstruction()
{ 
  delete fMessenger;
}

// -- Espesores --
void DetectorConstruction::SetThickness(G4double val)
{
  fThickness = val;
}

void DetectorConstruction::SetAThickness(G4double val)
{
  aThickness = val;
}

// -- Construcción del detector --
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Llamado a la base de datos del NIST
  G4NistManager* nist = G4NistManager::Instance();

  // Definición del "vacío" -> Equivalente al Galactic
  G4double presion, temperatura, densidad;
  densidad     = universe_mean_density;    //from PhysicalConstants.h
  presion    = 3.e-18*pascal;
  temperatura = 2.73*kelvin;

  G4Material* Vacuum   = new G4Material("Vacuum", 1., 1.01*g/mole, densidad, kStateGas,temperatura,presion);

  //-----------------------------------------------------------------------

  // Definición de los materiales (Primera configuración)
  G4Material* boxPb = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* boxConc = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4Material* boxGal = nist->FindOrBuildMaterial("G4_Galactic");

  // Segunda configuración 
  /*
  G4Material* boxPoly = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* boxAl = nist->FindOrBuildMaterial("G4_Al");
  */

  // -- Mundo --
  G4double world_sizeXY = 2.0*meter;
  G4double world_sizeZ  = 2.0*meter;
  
  // Solid volume
  G4Box* solidWorld = new G4Box("World",
				0.5*world_sizeXY,
				0.5*world_sizeXY,
				0.5*world_sizeZ); //its size
  
  // Logical volume
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        Vacuum,         //its material
                        "World");            //its name
  
  // Physical volume
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps 



  // Dimensiones de las cajas
  G4double boxHLX   = 0.005*cm;
  G4double boxHLY   = 0.005*cm;

  // -- Geometría dependiente de parámetros --
  // Pb
  G4Box* solidPb = new G4Box("BoxPb", boxHLX, boxHLY, fThickness/2.0);
  G4LogicalVolume* logicPb = new G4LogicalVolume(solidPb, boxPb, "BoxPb");

  new G4PVPlacement(0,
    G4ThreeVector(0,0,0),
    logicPb, "BoxPb",
    logicWorld, false, 0, fCheckOverlaps);

  // Gap 1
  G4Box* solidGap1 = new G4Box("Box2", boxHLX, boxHLY, fThickness/2.0);
  G4LogicalVolume* logicGap1 = new G4LogicalVolume(solidGap1, boxGal, "Box2");

  new G4PVPlacement(0,
    G4ThreeVector(0,0,fThickness),
    logicGap1, "Box2",
    logicWorld, false, 0, fCheckOverlaps);

  // Concreto
  G4Box* solidConc = new G4Box("Box3", boxHLX, boxHLY, aThickness/2.0);
  G4LogicalVolume* logicConc = new G4LogicalVolume(solidConc, boxConc, "Box3");

  new G4PVPlacement(0,
    G4ThreeVector(0,0,fThickness + aThickness/2.0 + fThickness/2.0),
    logicConc, "Box3",
    logicWorld, false, 0, fCheckOverlaps);

  // Gap 2
  G4Box* solidGap2 = new G4Box("Box4", boxHLX, boxHLY, aThickness/2.0);
  G4LogicalVolume* logicGap2 = new G4LogicalVolume(solidGap2, boxGal, "Box4");

  new G4PVPlacement(0,
    G4ThreeVector(0,0,fThickness + aThickness + fThickness),
    logicGap2, "Box4",
    logicWorld, false, 0, fCheckOverlaps);

  // -- Atributos de Visualización --
  logicPb->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));
  logicConc->SetVisAttributes(new G4VisAttributes(G4Colour::Brown()));
  logicGap1->SetVisAttributes(G4VisAttributes::GetInvisible());
  logicGap2->SetVisAttributes(G4VisAttributes::GetInvisible());

  return physWorld;
}
