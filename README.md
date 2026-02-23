# Proyecto ICTP 🥼🧬🕰

## Estructura del proyecto

Geant4_Shielding_Project/
├── CMakeLists.txt             # Instrucciones de compilación para CMake
├── shielding_sim.cc           # El archivo principal (main)
├── include/                   # Archivos de cabecera (.hh)
│   ├── DetectorConstruction.hh
│   ├── PhysicsList.hh
│   ├── PrimaryGeneratorAction.hh
│   ├── ActionInitialization.hh
│   ├── RunAction.hh
│   └── SteppingAction.hh      <-- Vital para tu conteo de fluencia
├── src/                       # Implementación del código (.cc)
│   ├── DetectorConstruction.cc
│   ├── PhysicsList.cc
│   ├── PrimaryGeneratorAction.cc
│   ├── ActionInitialization.cc
│   ├── RunAction.cc
│   └── SteppingAction.cc
├── macros/                    # Scripts de control de Geant4 (.mac)
│   ├── init_vis.mac           # Para abrir la interfaz gráfica (GUI)
│   └── run_batch.mac          # Para corridas largas sin gráficos
├── analysis/                  # Tu post-procesamiento en Python
│   ├── process_data.py        # Script de Pandas
│   └── requirements.txt       # Librerías de Python necesarias
├── .gitignore                 # Para no subir archivos basura al repo
└── README.md                  # Descripción de tu proyecto
