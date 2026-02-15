// ---------- Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS -----
// @author: Angela Sofia Malagon Palomino 
// --------------------------------------------------------------------------------------------------------------------------
// -- Main function --
# include "MyPhysicsList.hh"  // Adición de procesos fisicos 
# include "MyPrimaryGenerator.hh" // Definicion del evento primario (cinematica)

int main() {

    G4RunManager* runManager=new G4RunManager; // Ejecución

    runManager->SetUserInitializacion(new MyDetectorConstruction); // Geometría
    runManager->SetUserInitialization(new MyPhysicsList); // La fisica
    runManager->SetUserAction(new MyPrimaryGenerator); // La cinematica del evento generado
    runManager->Initialize(); // Inicialización

    G4UImanager* UI=G4UImanager::GetUIpointer(); // Puntero a la interfaz de usuario
    UI->ApplyCommand("run/verbose 1"); // Nivel de la ejecución
    int numberOfEvent=3; // Número de eventos a ser ejecutados
    runManager->BeamOn(numberOfEvent); // Generación de eventos
    delete runManager; // Fin de la ejecución
    return 0;
}