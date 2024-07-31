cmake_minimum_required(VERSION 3.30)

project(Hand VERSION 0.0.0)

include(cmake/deps.cmake)

add_library(
    Hand
    INTERFACE
    )

add_library(
    hand::hand
    ALIAS
    Hand
    )

target_sources(
    Hand
    INTERFACE FILE_SET
              HEADERS
              BASE_DIRS
              "src/include"
    )

target_link_libraries(
    Hand
    INTERFACE free-audio::clap
              free-audio::clap-helpers
    )

target_compile_features(
    Hand
    INTERFACE c_std_17
              cxx_std_23
    )

target_compile_options(
    Hand
    INTERFACE $<$<CXX_COMPILER_ID:MSVC>:
              /W4
              /WX
              /MP
              /nologo
              /wd4100
              /wd4127
              /utf-8
              /bigobj
              /diagnostics:caret
              /Zc:__cplusplus
              >
              $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>>:
              /W4
              /WX
              /nologo
              /wd4100
              /wd4127
              /utf-8
              /bigobj
              /diagnostics:caret
              /Zc:__cplusplus
              -Wno-braced-scalar-init
              -Wno-nonportable-include-path
              >
              $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:GNU>>:
              -Wall
              -Werror
              -Wextra
              -Wpedantic
              -Wno-unused-parameter
              -Wno-braced-scalar-init
              -Wno-language-extension-token
              >
    )

target_link_options(
    Hand
    INTERFACE
    $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:
    /WX
    /NOLOGO
    >
    $<$<CXX_COMPILER_FRONTEND_VARIANT:GNU>:
    -Wl,/WX,/NOLOGO
    >
    )

if(CMAKE_SYSTEM_NAME
   STREQUAL
   "Windows"
    )
    target_link_libraries(Hand INTERFACE glow::glow)

    target_compile_definitions(
        Hand
        INTERFACE NOMINMAX
                  WIN32_LEAN_AND_MEAN
                  PLATFORM_WINDOWS=1
                  OPERATING_SYSTEM="Windows"
                  $<$<CONFIG:Debug>:HOT_RELOAD=1>
                  DEV_URL="https://localhost:5173"
        )
endif()

include(cmake/hand_plugin.cmake)
include(cmake/plugin.cmake)
