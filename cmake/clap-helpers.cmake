FetchContent_Declare(
    free-audio_clap-helpers
    URL "https://github.com/free-audio/clap-helpers/archive/58ab81b1dc8219e859529c1306f364bb3aedf7d5.zip"
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
