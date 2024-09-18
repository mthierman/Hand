cmake_minimum_required(VERSION 3.30)

project(Hand VERSION 0.0.0)

if(NOT
   DEFINED
   CMAKE_MSVC_RUNTIME_LIBRARY
    )
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

if(NOT
   DEFINED
   CLAP_WRAPPER_CXX_STANDARD
    )
    set(CLAP_WRAPPER_CXX_STANDARD 17)
endif()

set(CLAP_WRAPPER_DONT_ADD_TARGETS ON)

set(CMAKE_DEBUG_POSTFIX "")

set(CMAKE_CXX_STANDARD ${CLAP_WRAPPER_CXX_STANDARD})

list(
    APPEND
    CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
    )

include(FetchContent)
include(clap)
include(clap-helpers)
include(clap-wrapper)
include(Glow)

function(hand_add_plugin)
    set(args
        ID
        NAME
        VENDOR
        URL
        MANUAL_URL
        SUPPORT_URL
        VERSION
        DESCRIPTION
        )
    set(listArgs
        SOURCES
        FEATURES
        )
    cmake_parse_arguments(
        PLUGIN
        ""
        "${args}"
        "${listArgs}"
        ${ARGN}
        )

    if(NOT
       PLUGIN_ID
        )
        message(FATAL_ERROR "Plugin ID is mandatory")
    endif()

    if(NOT
       PLUGIN_NAME
        )
        message(FATAL_ERROR "Plugin name is mandatory")
    endif()

    list(
        TRANSFORM
        PLUGIN_FEATURES
        REPLACE "(.+)"
                "\"\\1\""
                OUTPUT_VARIABLE
                PLUGIN_FEATURES
        )

    list(
        APPEND
        PLUGIN_FEATURES
        "static_cast<const char*>(nullptr)"
        )

    list(
        JOIN
        PLUGIN_FEATURES
        ", "
        PLUGIN_FEATURES
        )

    configure_file(
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/config/descriptor.cxx"
        "${CMAKE_CURRENT_BINARY_DIR}/config/descriptor.cxx"
        )

    add_library(
        ${PLUGIN_NAME}_base
        STATIC
        )

    target_compile_features(
        ${PLUGIN_NAME}_base
        PUBLIC c_std_17
               cxx_std_23
        )

    target_sources(
        ${PLUGIN_NAME}_base
        PRIVATE ${PLUGIN_SOURCES}
                "${CMAKE_CURRENT_BINARY_DIR}/config/descriptor.cxx"
                "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/helper.cxx"
                "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/factory.cxx"
                "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/event.cxx"
        PUBLIC FILE_SET
               HEADERS
               BASE_DIRS
               "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/include"
        )

    target_compile_definitions(
        ${PLUGIN_NAME}_base
        PUBLIC $<$<CONFIG:Debug>:HOT_RELOAD=1>
               DEV_URL="http://localhost:5173"
        )

    target_link_libraries(
        ${PLUGIN_NAME}_base
        PUBLIC free-audio::clap
               free-audio::clap-helpers
        )

    target_compile_options(
        ${PLUGIN_NAME}_base
        PUBLIC $<$<CXX_COMPILER_ID:MSVC>:
               /MP
               /utf-8
               /bigobj
               /diagnostics:caret
               /Zc:__cplusplus
               >
               $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:
               /W4
               /WX
               /wd4100
               /wd4127
               >
               $<$<CXX_COMPILER_FRONTEND_VARIANT:GNU>:
               -Wall
               -Werror
               >
        PUBLIC $<$<CXX_COMPILER_ID:Clang>:
               -Wno-braced-scalar-init
               -Wno-extra-semi
               -Wno-gnu-zero-variadic-macro-arguments
               -Wno-language-extension-token
               -Wno-microsoft-enum-value
               -Wno-nonportable-include-path
               -Wno-unused-parameter
               >
        )

    target_link_options(
        ${PLUGIN_NAME}_base
        PUBLIC
        $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:
        /WX
        >
        $<$<CXX_COMPILER_FRONTEND_VARIANT:GNU>:
        -Wl,/WX
        >
        )

    add_library(
        ${PLUGIN_NAME}
        MODULE
        )

    target_sources(${PLUGIN_NAME} PRIVATE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/entry.cxx")

    target_link_libraries(${PLUGIN_NAME} PRIVATE ${PLUGIN_NAME}_base)

    add_executable(${PLUGIN_NAME}_standalone)

    target_sources(
        ${PLUGIN_NAME}_standalone PRIVATE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/entry.cxx"
        )

    target_link_libraries(${PLUGIN_NAME}_standalone PRIVATE ${PLUGIN_NAME}_base)

    target_add_standalone_wrapper(
        TARGET
        ${PLUGIN_NAME}_standalone
        OUTPUT_NAME
        ${PLUGIN_NAME}
        STATICALLY_LINKED_CLAP_ENTRY
        TRUE
        PLUGIN_ID
        ${PLUGIN_ID}
        )

    if(CMAKE_SYSTEM_NAME
       STREQUAL
       "Windows"
        )
        target_sources(
            ${PLUGIN_NAME}_base
            PRIVATE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/platform/windows/dll_main.cxx"
                    "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/platform/windows/gui.cxx"
            )

        target_link_libraries(${PLUGIN_NAME}_base PUBLIC glow::glow)

        target_compile_definitions(
            ${PLUGIN_NAME}_base
            PUBLIC PLATFORM_WINDOWS=1
                   OPERATING_SYSTEM="Windows"
            )

        set_target_properties(
            ${PLUGIN_NAME}
            PROPERTIES SUFFIX
                       ".clap"
            )
    endif()
endfunction()

if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory(examples)
endif()
