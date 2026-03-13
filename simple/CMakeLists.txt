# -- CMakefile --
cmake_minimum_required(VERSION 3.16...3.27)
project(B1)

find_package(Geant4 REQUIRED ui_all vis_all)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(simple simple.cc ${sources} ${headers})
target_include_directories(simple PRIVATE include)
target_link_libraries(simple PRIVATE ${Geant4_LIBRARIES})

set(SIMPLE_SCRIPTS
  #simple.in
  #simple.out
  init_vis.mac
  run1.mac
  #run2.mac
  run3.mac
  vis.mac
  )

foreach(_script ${SIMPLE_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
