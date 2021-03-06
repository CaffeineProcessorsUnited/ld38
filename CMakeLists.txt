cmake_minimum_required(VERSION 2.8)
PROJECT(LD38)

option(SANITIZE_ADDRESS "" On)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})
add_subdirectory(CPU)
find_library(CPU REQUIRED)

set(GAME_NAME LD38)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set(ARCH_DIR "x64" )
    set(ARCH_DEPS_DIR "x86_64" )
else()
    set(ARCH_DIR "x86" )
    set(ARCH_DEPS_DIR "x86" )
endif()

find_package(GamePlay)

if ( NOT GAMEPLAY_SRC_PATH )
    set(GAMEPLAY_SRC_PATH "~/build/GamePlay")
endif()
message(${GAMEPLAY_SRC_PATH})

set(GAMEPLAY_EXT_LIBS_PATH "${GAMEPLAY_SRC_PATH}/external-deps/lib")

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    ADD_DEFINITIONS(-D__linux__)
    ADD_DEFINITIONS(-std=c++11)
    SET(TARGET_OS "LINUX")
    SET(TARGET_OS_DIR "linux")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    ADD_DEFINITIONS(-std=c++11)
    SET(TARGET_OS "OSX")
    SET(TARGET_OS_DIR "Mac")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    IF(MSVC)
        ADD_DEFINITIONS(-DMSVC)
    ENDIF(MSVC)
    ADD_DEFINITIONS(-DWIN32)
    ADD_DEFINITIONS(-D_WINDOWS)
    SET(TARGET_OS "WINDOWS")
    SET(TARGET_OS_DIR "windows")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

set(GAME_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${TARGET_OS_DIR}")

macro (append_gameplay_lib listToAppend)
    set(libName gameplay)
    IF (TARGET_OS STREQUAL "WINDOWS")
		FIND_LIBRARY(${libName}_LIBRARY_RELEASE
			NAMES ${libName}
			PATHS "${GAMEPLAY_SRC_PATH}/gameplay/${TARGET_OS_DIR}/${ARCH_DIR}/Release"
		)

		FIND_LIBRARY(${libName}_LIBRARY_DEBUG
			NAMES ${libName}
			PATHS "${GAMEPLAY_SRC_PATH}/gameplay/${TARGET_OS_DIR}/${ARCH_DIR}/Debug"
		)
		SET(FOUND_LIB_${libName}
			debug ${${libName}_LIBRARY_DEBUG}
			optimized ${${libName}_LIBRARY_RELEASE}
		)
	ELSE (TARGET_OS STREQUAL "WINDOWS")
		find_library(FOUND_LIB_${libName} ${libName} HINTS
			"${GAMEPLAY_SRC_PATH}/cmake/gameplay" "${GAMEPLAY_SRC_PATH}/build/gameplay" "${GAMEPLAY_SRC_PATH}/gameplay/src")
	ENDIF (TARGET_OS STREQUAL "WINDOWS")
	set(${listToAppend} ${${listToAppend}} ${FOUND_LIB_${libName}})
endmacro(append_gameplay_lib)

macro (append_gameplay_ext_lib listToAppend libName libDirName)
    string(TOLOWER ${CMAKE_SYSTEM_NAME} systemName)
    IF("${libDirName}" STREQUAL "")
		find_library(FOUND_LIB_${libName} NAMES ${libName} ${ARGN})
    ELSE("${libDirName}" STREQUAL "")
        set(pathToSearch
            "${GAMEPLAY_EXT_LIBS_PATH}/${systemName}/${ARCH_DEPS_DIR}")
		find_library(FOUND_LIB_${libName} NAMES ${libName} ${ARGN} HINTS ${pathToSearch})
    ENDIF("${libDirName}" STREQUAL "")

    set(${listToAppend} ${${listToAppend}} ${FOUND_LIB_${libName}})
    message(STATUS "Library Found: ${libName} Path: ${FOUND_LIB_${libName}}")
endmacro (append_gameplay_ext_lib)

macro(copy_files TARGET_NAME GLOBPAT SOURCE DESTINATION RECUR)
    get_filename_component(REALPATH_SOURCE ${SOURCE} REALPATH)
    IF(${RECUR})
        SET(RECURSE_PARAM GLOB_RECURSE)
    ELSEIF(NOT ${RECUR})
        SET(RECURSE_PARAM GLOB)
    ENDIF(${RECUR})
    file(${RECURSE_PARAM} COPY_FILES RELATIVE ${REALPATH_SOURCE} "${REALPATH_SOURCE}/${GLOBPAT}")

  add_custom_target(${TARGET_NAME} ALL COMMENT "Copying files: ${REALPATH_SOURCE}/${GLOBPAT}")

  foreach(FILENAME ${COPY_FILES})
    set(SRC "${REALPATH_SOURCE}/${FILENAME}")
    set(DST "${DESTINATION}/${FILENAME}")

    IF(IS_DIRECTORY ${SRC})
        add_custom_command(TARGET ${TARGET_NAME} COMMAND ${CMAKE_COMMAND} -E make_directory ${DST})
    ELSE(IS_DIRECTORY ${SRC})
        add_custom_command(TARGET ${TARGET_NAME} COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC} ${DST})
    ENDIF(IS_DIRECTORY ${SRC})
  endforeach(FILENAME)
endmacro(copy_files)

include_directories( 
    ${GAMEPLAY_SRC_PATH}/gameplay/src
    ${GAMEPLAY_SRC_PATH}/external-deps/include
)

append_gameplay_lib(GAMEPLAY_LIBRARIES)
append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "gameplay-deps" "libs")

IF (TARGET_OS STREQUAL "LINUX")
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "GL" "")
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "m" "" )
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "X11" "")
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "dl" "")
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "rt" "" )
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "pthread" "" )
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "gtk-x11-2.0" "" )
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "gobject-2.0" "" )
	append_gameplay_ext_lib(GAMEPLAY_LIBRARIES "glib-2.0" "" )
ELSEIF (TARGET_OS STREQUAL "OSX")
    find_package(OpenGL REQUIRED)
    FIND_LIBRARY(AGL_LIBRARY AGL)
    FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices )
    FIND_LIBRARY(ATBOX_LIBRARY AudioToolbox)
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    FIND_LIBRARY(CAUDIO_LIBRARY CoreAudio)
    FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
    FIND_LIBRARY(CFOUNDATION_LIBRARY CoreFoundation)
    FIND_LIBRARY(CSERVICES_LIBRARY CoreServices)
    FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
    FIND_LIBRARY(QUICKTIME_LIBRARY QuickTime )
    FIND_LIBRARY(IOKIT_LIBRARY IOKit )
    FIND_LIBRARY(AVF_LIBRARY AVFoundation)
    FIND_LIBRARY(OAL_LIBRARY OpenAL)
    FIND_LIBRARY(GKIT_LIBRARY GameKit)
    SET(FRAMEWORK_LIBRS
        ${AGL_LIBRARY}
        ${APP_SERVICES_LIBRARY}
        ${ATBOX_LIBRARY}
        ${CARBON_LIBRARY}
        ${CAUDIO_LIBRARY}
        ${COREVIDEO_LIBRARY}
        ${CFOUNDATION_LIBRARY}
        ${CSERVICES_LIBRARY}
        ${OAL_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GKIT_LIBRARY}
        ${IOKIT_LIBRARY}
        "-framework Foundation"
        "-framework Cocoa")
    set(GAMEPLAY_LIBRARIES ${GAMEPLAY_LIBRARIES}
        stdc++
        gameplay
        gameplay-deps
        m
        dl
        pthread
        ${FRAMEWORK_LIBRS}
        )
ELSEIF (TARGET_OS STREQUAL "WINDOWS")
	set(GAMEPLAY_LIBRARIES ${GAMEPLAY_LIBRARIES} "OpenGL32")
	set(GAMEPLAY_LIBRARIES ${GAMEPLAY_LIBRARIES} "GLU32")
	ADD_DEFINITIONS(-D_ITERATOR_DEBUG_LEVEL=0)
ENDIF (TARGET_OS STREQUAL "LINUX")

source_group(res FILES ${GAME_RES} ${GAMEPLAY_RES} ${GAME_RES_SHADERS} ${GAME_RES_SHADERS_LIB})
source_group(src FILES ${GAME_SRC})

set(GAME_SRC
    src/LD38.cpp
    src/LD38.h
    src/Screens/TestScreen.cpp
    src/Screens/TestScreen.h
    src/gamelogic/World.cpp
    src/gamelogic/World.h
    src/gamelogic/WorldObject.cpp
    src/gamelogic/WorldObject.h
    src/worldobjects/RandomCloud.cpp
    src/worldobjects/RandomCloud.h
    src/worldobjects/RandomStar.cpp
    src/worldobjects/RandomStar.h
    src/worldobjects/Background.cpp
    src/worldobjects/Background.h
    src/worldobjects/Unicorn.h
    src/worldobjects/Unicorn.cpp
    src/gamelogic/WorldObjectSingle.cpp
    src/gamelogic/WorldObjectSingle.h
    src/gamelogic/WorldResource.h
    src/gamelogic/WorldObjectAction.h
    src/gamelogic/WorldObjectAction.cpp
    src/gamelogic/ActionSelector.h
    src/gamelogic/ActionSelector.cpp
    src/gamelogic/UnicornAction.h
    src/gamelogic/UnicornAction.cpp
    src/worldobjects/RainbowTree.cpp
    src/worldobjects/RainbowTree.h
    src/worldobjects/Granny.cpp
    src/worldobjects/Granny.h
    src/fw_decl.h
    ${CPU_SOURCE}
        src/worldobjects/Rain.h src/worldobjects/Rain.cpp src/Screens/MainMenu.cpp src/Screens/MainMenu.h src/worldobjects/Sun.cpp src/worldobjects/Sun.h)

find_package(Sanitizers)

add_executable(${GAME_NAME}
	WIN32
	MACOSX_BUNDLE
    ${GAME_SRC}
)

target_link_libraries(${GAME_NAME} ${GAMEPLAY_LIBRARIES} CPU)

set_target_properties(${GAME_NAME} PROPERTIES
    OUTPUT_NAME "${GAME_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${GAME_OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${GAME_OUTPUT_DIR}"
)

add_sanitizers(${GAME_NAME})

#TODO: Copy res files to the bin dir, it is done that way so we can make post
#processing to the the res files in the future like zipping or preparation to
#per platfom format.
IF (TARGET_OS STREQUAL "OSX")
	SET(TARGET_RESOURCE_BASE_DIR "$<TARGET_FILE_DIR:${GAME_NAME}>/../Resources")
ELSE(TARGET_OS STREQUAL "OSX")
	SET(TARGET_RESOURCE_BASE_DIR "$<TARGET_FILE_DIR:${GAME_NAME}>")
ENDIF(TARGET_OS STREQUAL "OSX")

copy_files(CopyRes * "${CMAKE_SOURCE_DIR}/res" "${TARGET_RESOURCE_BASE_DIR}/res" 1)
copy_files(CopyShaders * "${GAMEPLAY_SRC_PATH}/gameplay/res/shaders" "${TARGET_RESOURCE_BASE_DIR}/res/shaders" 1)
copy_files(CopyConfig *.config "${CMAKE_SOURCE_DIR}" "${TARGET_RESOURCE_BASE_DIR}" 0)
