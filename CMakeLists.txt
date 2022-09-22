cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Pi-SP_sim)

set(CMAKE_CXX_FLAGS " -stdlib=libc++ -pthread -std=c++17 -m64 -I/opt/homebrew/Cellar/root/6.26.06_1/include/root -L/opt/homebrew/Cellar/root/6.26.06_1/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/opt/homebrew/Cellar/root/6.26.06_1/lib/root -stdlib=libc++ -lpthread -lm -ldl")

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

add_custom_target(Pi-SP_sim DEPENDS sim)
