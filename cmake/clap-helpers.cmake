FetchContent_Declare(
    free-audio_clap-helpers
    URL "https://github.com/free-audio/clap-helpers/archive/refs/heads/main.zip"
    DOWNLOAD_NO_PROGRESS TRUE
    SOURCE_SUBDIR
    "NULL"
    )

FetchContent_MakeAvailable(free-audio_clap-helpers)

add_library(
    free-audio_clap-helpers
    INTERFACE
    )

add_library(
    free-audio::clap-helpers
    ALIAS
    free-audio_clap-helpers
    )

target_sources(
    free-audio_clap-helpers
    INTERFACE FILE_SET
              HEADERS
              BASE_DIRS
              "${free-audio_clap-helpers_SOURCE_DIR}/include"
    )
