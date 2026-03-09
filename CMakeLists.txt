# --- CMakeLists.txt ---
cmake_minimum_required(VERSION 3.16)
project(ShieldingSimulation)

# 1. Encontrar Geant4 y sus configuraciones
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# 2. INDICAR LA RUTA DE LOS ENCABEZADOS (.hh)
# Esto resuelve el error "No such file or directory"
include_directories(${PROJECT_SOURCE_DIR}/include)

# 3. RECOLECTAR LOS ARCHIVOS
# Buscamos los .cc en la carpeta src
file(GLOB_RECURSE sources "${PROJECT_SOURCE_DIR}/src/*.cc")
# Buscamos el main.cc (asumiendo que está en la raíz o en src)
# Si tu main.cc está dentro de src, cambia la ruta abajo a src/main.cc
set(MAIN_SOURCE Main.cc) 

# 4. CREAR EL EJECUTABLE
add_executable(ShieldingSimulation ${MAIN_SOURCE} ${sources})

# 5. VINCULAR LIBRERÍAS
target_link_libraries(ShieldingSimulation ${Geant4_LIBRARIES})

# 6. COPIAR MACROS (Opcional pero útil)
# Esto copia tus archivos .mac a la carpeta build automáticamente
set(SCRIPTS vis.mac)
foreach(_script ${SCRIPTS})
  configure_file(${_script} ${_script} COPYONLY)
endforeach()