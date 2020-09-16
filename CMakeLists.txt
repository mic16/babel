# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.11)

# Notre projet est étiqueté babel_client
project(babel_client)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE RELEASE)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

# Crée des variables avec les fichiers à compiler
set(SRCS
    src/main_client.cpp
    )


add_definitions(-DDEBUG_PROFILE=0)
add_definitions(-Wno-pointer-arith)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_module")

find_package(Threads REQUIRED)

link_libraries(${CMAKE_THREAD_LIBS_INIT})

set(HEADERS
    )

# On indique que l'on veut un exécutable "babel_client" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(babel_client ${SRCS} ${HEADERS})

target_link_libraries(babel_client ${SFML_LIBRARIES})


project(babel_server)

set(SRCS
    src/main_server.cpp
    )

set(HEADERS
    )
add_executable(babel_server ${SRCS} ${HEADERS})
target_link_libraries(babel_server ${SFML_LIBRARIES})