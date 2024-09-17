FetchContent_Declare(
    free-audio_clap
    URL "https://github.com/free-audio/clap/archive/refs/tags/1.2.1.zip"
    DOWNLOAD_NO_PROGRESS TRUE
    SOURCE_SUBDIR
    "NULL"
    )

FetchContent_MakeAvailable(free-audio_clap)

add_library(
    free-audio_clap
    INTERFACE
    )

add_library(
    free-audio::clap
    ALIAS
    free-audio_clap
    )

target_sources(
    free-audio_clap
    INTERFACE FILE_SET
              HEADERS
              BASE_DIRS
              "${free-audio_clap_SOURCE_DIR}/include"
    )
