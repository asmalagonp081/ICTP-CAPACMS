#include "MyDetectorConstruction.hh"
#include "MyPhysicsList.hh"
#include "MyPrimaryGenerator.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv) {
    // 1. Detectar si queremos interfaz gráfica o modo batch
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // 2. Construir el RunManager (el motor de la simulación)
    G4RunManager* runManager = new G4RunManager;

    // 3. Registrar nuestras clases obligatorias
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    
    // El PrimaryGenerator se registra de forma un poco distinta (UserAction)
    runManager->SetUserAction(new MyPrimaryGeneratorAction());

    // 4. Inicializar el visualizador
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 5. Obtener el puntero al Administrador de Interfaz de Usuario
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (!ui) {
        // Modo Batch (sin gráficos, para correr miles de eventos)
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // Modo Interactivo (con gráficos)
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // 6. Limpieza de memoria
    delete visManager;
    delete runManager;

    return 0;
}