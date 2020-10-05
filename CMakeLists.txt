# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.11)

# Notre projet est étiqueté Babel
project(Babel)

set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 2.8.12)
set (CMAKE_BUILD_TYPE RELEASE)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

# Crée des variables avec les fichiers à compiler
set(SRCSCLIENT
    src/client/main.cpp
    src/utils/Utils.cpp
    src/utils/Request.cpp
    )

set(SRCSSERVER
    src/server/main.cpp
    src/server/TcpConnection.cpp
    src/server/TcpServer.cpp
    src/server/ServerLogic.cpp
    src/utils/Utils.cpp
    src/utils/Request.cpp
    src/dataBase/Data.cpp
    )

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
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


set(HEADERSCLIENT
    src/client/LineWidget.hpp
    src/utils/Utils.hpp
    src/utils/Request.hpp
    )

set(HEADERSSERVER
    src/server/main.hpp
    src/server/TcpConnection.hpp
    src/server/TcpServer.hpp
    src/server/ServerLogic.hpp
    src/utils/Utils.hpp
    src/utils/Request.hpp
    src/dataBase/Data.hpp
    )

# On indique que l'on veut un exécutable "Babel" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(BabelServer ${SRCSSERVER} ${HEADERSSERVER})
add_executable(Babel ${SRCSCLIENT} ${HEADERSCLIENT})

target_link_libraries(Babel ${CONAN_LIBS} Qt5::Widgets)
target_link_libraries(BabelServer ${CONAN_LIBS} sqlite3)