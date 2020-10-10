# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.14)

# Notre projet est étiqueté Babel
project(Babel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (EXISTS /home/$ENV{USER}/Qt)
    if (EXISTS /home/$ENV{USER}/Qt/5.14.2)
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
        set(CMAKE_AUTOUIC ON)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTORCC ON)

        set(CONFIG += qmltypes)
        set(QML_IMPORT_NAME = io.qt.examples.backend)
        set(QML_IMPORT_MAJOR_VERSION = 1)

        set(Qt5Quick_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5Quick)
        set(Qt5QuickControls2_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5QuickControls2)
        set(Qt5Qml_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5Qml)
        set(Qt5QmlModels_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5QmlModels)
        set(Qt5Network_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5Network)
        set(Qt5Gui_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5Gui)
        set(Qt5Core_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5Core)

        set(Qt5_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5)
        set(QT_DIR /home/$ENV{USER}/Qt/5.14.2/gcc_64/lib/cmake/Qt5)

        find_package(QT NAMES Qt5 COMPONENTS
            Core
            Network
            Gui
            Quick
            QuickControls2
        REQUIRED)
        find_package(Qt5 COMPONENTS
            Core
            Network
            Gui
            Quick
            QuickControls2
        REQUIRED)



        cmake_minimum_required(VERSION 2.8.12)
        set (CMAKE_BUILD_TYPE RELEASE)

        cmake_policy(SET CMP0028 NEW)
        # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

        # Crée des variables avec les fichiers à compiler
        set(SRCSCLIENT
            src/client/main.cpp
            src/client/qml.qrc
            src/utils/Utils.cpp
            src/utils/Request.cpp
            src/client/backend.cpp
            src/client/mainwindow.cpp
            src/client/Communication.cpp
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
        find_package(Qt5Core CONFIG REQUIRED)

        include_directories(${CMAKE_INCLUDE_PATH})

        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_module")

        # find_package(Threads REQUIRED)

        # link_libraries(${CMAKE_THREAD_LIBS_INIT})


        set(HEADERSCLIENT
            src/client/backend.hpp
            src/utils/Utils.hpp
            src/utils/Request.hpp
            src/client/mainwindow.hpp
            src/client/Communication.hpp
            src/client/Clock.hpp
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

        target_compile_definitions(Babel
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

        target_link_libraries(Babel PRIVATE ${CONAN_LIBS} Qt5::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
        target_link_libraries(BabelServer ${CONAN_LIBS} sqlite3)
    else()
        set(HEADERSCLIENT
            src/error/main.cpp
        )

        set(HEADERSSERVER
        )

        # On indique que l'on veut un exécutable "Babel" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
        add_executable(Babel ${SRCSCLIENT} ${HEADERSCLIENT})
    endif()
else()
    set(HEADERSCLIENT
        src/error/main.cpp
    )

    set(HEADERSSERVER
    )

    # On indique que l'on veut un exécutable "Babel" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
    add_executable(Babel ${SRCSCLIENT} ${HEADERSCLIENT})
endif()