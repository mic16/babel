# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.11)

# Notre projet est étiqueté Babel
project(Babel)

set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 2.8.12)
set (CMAKE_BUILD_TYPE RELEASE)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

# Crée des variables avec les fichiers à compiler
set(SRCS
    src/client/main.cpp
    # src/client/PortAudioEcho.cpp
    src/client/PortAudioRecord.cpp
    )


add_definitions(-DDEBUG_PROFILE=0)
add_definitions(-Wno-pointer-arith)
add_definitions("-fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_module")

find_package(Threads REQUIRED)

link_libraries(${CMAKE_THREAD_LIBS_INIT})

set(HEADERS
    src/client/LineWidget.hpp
    )

# On indique que l'on veut un exécutable "Babel" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(Babel ${SRCS} ${HEADERS})

target_link_libraries(Babel ${CONAN_LIBS} Qt5::Widgets)