// // SIMULACIÓN DE ATENUACIÓN DE RAYOS GAMMA USANDO G4 Y MULASSIS
#include "RE03UserScoreWriter.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4SDParticleFilter.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VScoringMesh.hh"

#include <fstream>
#include <map>

RE03UserScoreWriter::RE03UserScoreWriter() : G4VScoreWriter()
{
  ;
}

RE03UserScoreWriter::~RE03UserScoreWriter()
{
  ;
}

void RE03UserScoreWriter::DumpQuantityToFile(const G4String& psName, const G4String& fileName,
                                             const G4String& option)
{
  using MeshScoreMap = G4VScoringMesh::MeshScoreMap;
  //
  if (verboseLevel > 0) {
    G4cout << "User-defined DumpQuantityToFile() method is invoked." << G4endl;
    G4cout << "  -- to obtain a projection of the quantity <" << psName << "> onto the x-y plane --"
           << G4endl;
  }

  // change the option string into lowercase to the case-insensitive.
  G4String opt = option;
  std::transform(opt.begin(), opt.end(), opt.begin(), (int (*)(int))(tolower));

  // confirm the option
  if (opt.size() == 0) opt = "csv";

  // open the file
  std::ofstream ofile(fileName);
  if (!ofile) {
    G4cerr << "ERROR : DumpToFile : File open error -> " << fileName << G4endl;
    return;
  }
  ofile << "# mesh name: " << fScoringMesh->GetWorldName() << G4endl;

  // retrieve the map
  MeshScoreMap scMap = fScoringMesh->GetScoreMap();

  MeshScoreMap::const_iterator msMapItr = scMap.find(psName);
  if (msMapItr == scMap.end()) {
    G4cerr << "ERROR : DumpToFile : Unknown quantity, \"" << psName << "\"." << G4endl;
    return;
  }
  std::map<G4int, G4StatDouble*>* score = msMapItr->second->GetMap();
  ofile << "# primitive scorer name: " << msMapItr->first << G4endl;

  // write header info
  ofile << "# xy projection" << G4endl;
  ofile << fNMeshSegments[0] << " " << fNMeshSegments[1] << " " << G4endl;

  // declare xy array
  std::vector<double> projy;
  for (int y = 0; y < fNMeshSegments[1]; y++)
    projy.push_back(0.);
  std::vector<std::vector<double>> projxy;
  for (int x = 0; x < fNMeshSegments[0]; x++)
    projxy.push_back(projy);
  // accumulate
  ofile << std::setprecision(16);  // for double value with 8 bytes
  for (int x = 0; x < fNMeshSegments[0]; x++) {
    for (int y = 0; y < fNMeshSegments[1]; y++) {
      for (int z = 0; z < fNMeshSegments[2]; z++) {
        G4int idx = GetIndex(x, y, z);

        std::map<G4int, G4StatDouble*>::iterator value = score->find(idx);
        if (value != score->end()) projxy[x][y] += value->second->sum_wx();

      }  // z
    }  // y
  }  // x

  // write quantity
  ofile << std::setprecision(16);  // for double value with 8 bytes
  for (int x = 0; x < fNMeshSegments[0]; x++) {
    for (int y = 0; y < fNMeshSegments[1]; y++) {
      ofile << x << "," << y << ",";
      ofile << projxy[x][y] << G4endl;

    }  // y
  }  // x
  ofile << std::setprecision(6);

  // close the file
  ofile.close();
}
