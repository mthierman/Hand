cmake_minimum_required(VERSION 3.30)

project(hand VERSION 0.0.0)

include(cmake/deps.cmake)

add_library(
    hand
    INTERFACE
    )

add_library(
    hand::hand
    ALIAS
    hand
    )

target_sources(
    hand
    INTERFACE FILE_SET
              HEADERS
              BASE_DIRS
              "src/include"
    )

target_link_libraries(
    hand
    INTERFACE common::compile_features
              free-audio::clap
              free-audio::clap-helpers
    )

if(CMAKE_SYSTEM_NAME
   STREQUAL
   "Windows"
    )
    target_link_libraries(hand INTERFACE glow::glow)

    target_compile_options(
        hand
        INTERFACE $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:
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
        INTERFACE
        $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:
        /WX
        >
        $<$<CXX_COMPILER_FRONTEND_VARIANT:GNU>:
        -Wl,/WX
        >
        )

    target_compile_definitions(
        hand
        INTERFACE NOMINMAX
                  WIN32_LEAN_AND_MEAN
                  PLATFORM_WINDOWS=1
                  OPERATING_SYSTEM="Windows"
                  $<$<CONFIG:Debug>:HOT_RELOAD=1>
                  DEV_URL="https://localhost:5173"
        )
endif()

include(cmake/hand_plugin.cmake)

if(PROJECT_IS_TOP_LEVEL)
    hand_plugin(
        NAME
        "Example"
        VERSION
        "0.0.0"
        DESCRIPTION
        "Example plugin"
        VENDOR
        "Vendor"
        ID
        "com.vendor.example"
        URL
        "https://cleveraudio.org/"
        MANUAL_URL
        "https://cleveraudio.org/"
        SUPPORT_URL
        "https://cleveraudio.org/"
        SOURCES
        "example/example.cxx"
        FEATURES
        "audio-effect"
        "utility"
        )
endif()
