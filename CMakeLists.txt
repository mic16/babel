# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.11)

# Notre projet est étiqueté Babel
project(Babel)

set (CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOUIC ON)
cmake_minimum_required(VERSION 2.8.12)
set (CMAKE_BUILD_TYPE RELEASE)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -g3")

# Crée des variables avec les fichiers à compiler
set(SRCSCLIENT
    src/client/main.cpp
    src/client/mainwindow.cpp
    src/client/Communication.cpp
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

set(SRCSUDP
    src/udpclient/main.cpp
    src/udpclient/myudp.cpp
    )

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-DDEBUG_PROFILE=0)
add_definitions(-Wno-pointer-arith)
add_definitions("-fPIC")
add_definitions(${Qt5Widgets_DEFINITIONS})


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${Qt5Widgets_INCLUDES})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_module")

find_package(Threads REQUIRED)

link_libraries(${CMAKE_THREAD_LIBS_INIT})

set(HEADERSCLIENT
    src/client/mainwindow.hpp
    src/client/Communication.hpp
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

set(HEADERSUDP
    src/udpclient/myudp.hpp
    )

# On indique que l'on veut un exécutable "Babel" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(BabelServer ${SRCSSERVER} ${HEADERSSERVER})
add_executable(Babel ${SRCSCLIENT} ${HEADERSCLIENT})
add_executable(BabelUdp ${SRCSUDP} ${HEADERSUDP})

qt5_use_modules(Babel Network)
qt5_use_modules(BabelServer Network)
qt5_use_modules(BabelUdp Network)

target_link_libraries(Babel ${CONAN_LIBS} Qt5::Widgets)
target_link_libraries(BabelServer ${CONAN_LIBS} sqlite3)
target_link_libraries(BabelUdp ${CONAN_LIBS} Qt5::Widgets)
