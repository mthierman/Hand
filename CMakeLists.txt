cmake_minimum_required(VERSION 3.30)

project(hand VERSION 0.0.0)

include(cmake/deps.cmake)

add_library(hand)

add_library(
    hand::hand
    ALIAS
    hand
    )

target_sources(
    hand
    PRIVATE "src/include/plugin/plugin.hxx"
            "src/include/plugin/win32.hxx"
    PUBLIC FILE_SET
           HEADERS
           BASE_DIRS
           "src/include"
    )

target_link_libraries(
    hand
    PUBLIC common::compile_features
           free-audio::clap
           free-audio::clap-helpers
    )

if(CMAKE_SYSTEM_NAME
   STREQUAL
   "Windows"
    )
    target_link_libraries(hand PUBLIC glow::glow)

    target_compile_options(
        hand
        PUBLIC $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:
               /W4
               /WX
               /wd4100
               /wd4127
               /utf-8
               /bigobj
               /diagnostics:caret
               /Zc:__cplusplus
               >
               $<$<CXX_COMPILER_FRONTEND_VARIANT:GNU>:
               -Wall
               -Werror
               -Wextra
               -Wpedantic
               -Wno-unused-parameter
               -Wno-braced-scalar-init
               >
        )

    target_link_options(
        hand
        PUBLIC
        $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:
        /WX
        >
        $<$<CXX_COMPILER_FRONTEND_VARIANT:GNU>:
        -Wl,/WX
        >
        )

    target_compile_definitions(
        hand
        PUBLIC NOMINMAX
               WIN32_LEAN_AND_MEAN
               PLATFORM_WINDOWS=1
               OPERATING_SYSTEM="Windows"
               $<$<CONFIG:Debug>:HOT_RELOAD=1>
               DEV_URL="https://localhost:5173"
        )
endif()

include(cmake/hand_plugin.cmake)
