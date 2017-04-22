find_package(GamePlay)
option(SANITIZE_ADDRESS "" On)
find_package(Sanitizers)

include_directories(
        ${GAMEPLAY_SRC_PATH}/gameplay/src
        ${GAMEPLAY_SRC_PATH}/external-deps/include
)

ADD_DEFINITIONS(-std=c++11 -Wall)

set(CPU_SOURCE
        Common.h
        CPU.h
        Screen.cpp
        Screen.h
        ScreenForm.cpp
        ScreenForm.h
        ScreenManager.cpp
        ScreenManager.h
        SpriteBatch.cpp
        SpriteBatch.h
        App.cpp App.h
        EventHandler.h)
add_library(CPU SHARED ${CPU_SOURCE})

add_sanitizers(CPU)