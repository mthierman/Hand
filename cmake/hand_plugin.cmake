function(hand_plugin)
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

    add_library(
        ${PLUGIN_NAME}
        MODULE
        )

    configure_file(
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/descriptor.cxx"
        "${CMAKE_CURRENT_BINARY_DIR}/src/descriptor.cxx"
        )

    target_sources(
        ${PLUGIN_NAME}
        PRIVATE ${PLUGIN_SOURCES}
                "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/entry.cxx"
                "${CMAKE_CURRENT_BINARY_DIR}/src/descriptor.cxx"
        )

    target_link_libraries(${PLUGIN_NAME} PRIVATE hand::hand)

    if(CMAKE_SYSTEM_NAME
       STREQUAL
       "Windows"
        )
        set_target_properties(
            ${PLUGIN_NAME}
            PROPERTIES SUFFIX
                       ".clap"
            )
    endif()
endfunction()
