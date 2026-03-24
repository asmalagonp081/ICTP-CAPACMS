//
/// \file simple/src/RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
  : G4UserRunAction(),
    fAnalysisManager(G4AnalysisManager::Instance())
{
  // Crear histogramas
  fAnalysisManager->CreateH1("Egamma", "Energy of transmitted gammas", 100, 0., 1.0*MeV);
  fAnalysisManager->CreateH1("Transmitted", "Number of transmitted gammas per event", 50, 0, 50);

  // Crear ntuple para datos detallados
  fAnalysisManager->CreateNtuple("Photons", "Transmitted photon data");
  fAnalysisManager->CreateNtupleDColumn("Energy");
  fAnalysisManager->CreateNtupleDColumn("PositionZ");
  fAnalysisManager->CreateNtupleIColumn("EventID");
  fAnalysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  // Abrir archivo de salida
  fAnalysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4cout << "### Run " << run->GetRunID() << " end." << G4endl;

  // Escribir y cerrar archivo
  fAnalysisManager->Write();
  fAnalysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......