#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4GenericMessenger.hh"




class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  /// constructor
  DetectorConstruction();
  /// destructor
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  //Setters
  void SetThickness(G4double val);
  void SetAThickness(G4double val);
  
private:  
  G4bool  fCheckOverlaps;

  // Espesores
  G4double fThickness;
  G4double aThickness;
  
  //Messenger
  G4GenericMessenger* fMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

