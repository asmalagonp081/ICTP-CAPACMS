#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  /// constructor
  DetectorConstruction();
  /// destructor
  virtual ~DetectorConstruction();
  
public:
  /// Defines detector geom. and returns a pointer to the physical World Volume
  virtual G4VPhysicalVolume* Construct();
  
private:  
  G4bool  fCheckOverlaps;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

