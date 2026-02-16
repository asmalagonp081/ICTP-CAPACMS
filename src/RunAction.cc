// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- RunAction --

#include "G4RunManager.hh" // Controla el flujo del programa
#include "RunAction.hh" // Agrego el encabezado
#include "G4Run.hh" // Para usar G4Run
#include "G4AnalysisManager.hh" // Para crear CSV

UserRunAction::UserRunAction() : G4UserRunAction() {
    // Gestor de análsis para crear el csv
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("csv");
    analysisManager->CreateNtupleDColumn("E_inicial"); // MeV
    analysisManager->CreateNtupleIColumn("Cruce_Pb");
    analysisManager->CreateNtupleIColumn("Cruce_Conc");
    analysisManager->FinishNtuple();
}

void UserRunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    // Archivo de salida para el csv
    analysisManager->OpenFile("results.csv");
}

void UserRunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    // Cerrar el archivo al finalizar la simulación
    analysisManager->Write();
    analysisManager->CloseFile();
}