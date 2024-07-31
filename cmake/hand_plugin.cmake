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

    configure_file(
        ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/config/config.hxx
        ${CMAKE_CURRENT_BINARY_DIR}/include/config/config.hxx
        )

    target_include_directories(Hand PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)

    target_compile_definitions(
        Hand
        PUBLIC PLUGIN_ID="${PLUGIN_ID}"
               PLUGIN_NAME="${PLUGIN_NAME}"
               PLUGIN_VENDOR="${PLUGIN_VENDOR}"
               PLUGIN_URL="${PLUGIN_URL}"
               PLUGIN_MANUAL_URL="${PLUGIN_MANUAL_URL}"
               PLUGIN_SUPPORT_URL="${PLUGIN_SUPPORT_URL}"
               PLUGIN_VERSION="${PLUGIN_VERSION}"
               PLUGIN_DESCRIPTION="${PLUGIN_DESCRIPTION}"
        )

    add_library(
        ${PLUGIN_NAME}
        MODULE
        )

    list(
        JOIN
        PLUGIN_FEATURES
        ","
        PLUGIN_FEATURE_LIST
        )

    target_sources(${PLUGIN_NAME} PRIVATE ${PLUGIN_SOURCES})

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
