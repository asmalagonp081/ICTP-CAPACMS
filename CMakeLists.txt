# --- CMakeLists.txt ---
# 1. Definir la versión mínima de CMake y el nombre del proyecto 🏷️
cmake_minimum_required(VERSION 3.16...3.27)
project(shielding_sim)

# 2. Encontrar el paquete de Geant4 con sus componentes 🛠️
find_package(Geant4 REQUIRED ui_all vis_all)

# 3. Configurar las opciones de Geant4 (unidades, librerías, etc.) 📦
include(${Geant4_USE_FILE})

# 4. Definir dónde están tus archivos de cabecera (.hh) 📁
include_directories(${PROJECT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIRS})

# 5. Listar todos tus archivos de implementación (.cc) 📝
file(GLOB (http://file.GLOB) SOURCES src/*.cc Main.cc)

# 6. Crear el ejecutable final 🚀
add_executable(shielding_sim ${SOURCES})

# 7. Enlazar el ejecutable con las librerías de Geant4 🔗
target_link_libraries(shielding_sim ${Geant4_LIBRARIES})