// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Main function --
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh" // Lista de física estándar

int main(int argc, char** argv) {
    // 1. Detectar si el usuario quiere interfaz gráfica o ejecutar un script (lote)
    G4UIExecutive* ui = nullptr;
    if (argc == 1) { ui = new G4UIExecutive(argc, argv); }

    // 2. Crear el RunManager (el motor que coordina todo)
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 3. Registrar la Geometría (la clase que hicimos)
    runManager->SetUserInitialization(new DetectorConstruction());

    // 4. Registrar la Física
    // FTFP_BERT es una lista robusta para interacciones hadrónicas y electromagnéticas
    runManager->SetUserInitialization(new FTFP_BERT);

    // 5. Registrar las Acciones de Usuario (Generador, RunAction, etc.)
    // Esta clase actúa como el "puente" para registrar las demás acciones
    runManager->SetUserInitialization(new ActionInitialization());

    // 6. Inicializar el Administrador de Visualización
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 7. Obtener el puntero a la interfaz de usuario
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (!ui) {
        // Modo lote: se ejecuta un archivo .mac pasado por consola
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // Modo interactivo: abre la ventana gráfica
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Limpieza de memoria al cerrar
    delete visManager;
    delete runManager;

    return 0;
}