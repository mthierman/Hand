cmake_minimum_required(VERSION 3.30)

project(Hand VERSION 0.0.0)

include(cmake/deps.cmake)

add_library(Hand)

add_library(
    hand::hand
    ALIAS
    Hand
    )

target_sources(
    Hand
    PUBLIC "src/entry.cxx"
    PRIVATE "src/descriptor.cxx"
            "src/factory.cxx"
            "src/event.cxx"
    PUBLIC FILE_SET
           HEADERS
           BASE_DIRS
           "src/include"
    )

target_link_libraries(
    Hand
    PUBLIC common::compile_features
           common::link_options_lib
           free-audio::clap
           free-audio::clap-helpers
    )

target_compile_options(
    Hand
    PUBLIC $<$<CXX_COMPILER_ID:MSVC>:
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
           -Wno-braced-scalar-init
           -Wno-extra-semi
           -Wno-gnu-zero-variadic-macro-arguments
           -Wno-language-extension-token
           -Wno-microsoft-enum-value
           -Wno-nonportable-include-path
           -Wno-unused-parameter
           >
           $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:GNU>>:
           -Wall
           -Werror
           -Wno-braced-scalar-init
           -Wno-extra-semi
           -Wno-gnu-zero-variadic-macro-arguments
           -Wno-language-extension-token
           -Wno-microsoft-enum-value
           -Wno-nonportable-include-path
           -Wno-unused-parameter
           >
    )

target_compile_definitions(
    Hand
    PUBLIC $<$<CONFIG:Debug>:HOT_RELOAD=1>
           DEV_URL="https://localhost:5173"
    )

if(CMAKE_SYSTEM_NAME
   STREQUAL
   "Windows"
    )
    target_sources(Hand PRIVATE "src/gui_windows.cxx")

    target_link_libraries(
        Hand
        PUBLIC common::compile_definitions
               glow::glow
        )

    target_compile_definitions(
        Hand
        PUBLIC PLATFORM_WINDOWS=1
               OPERATING_SYSTEM="Windows"
        )
else()
    target_sources(Hand PRIVATE "src/gui.cxx")
endif()

include(cmake/hand_plugin.cmake)

add_subdirectory(examples)
