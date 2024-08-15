include(FetchContent)

FetchContent_Declare(
    cmake-modules URL "https://github.com/mthierman/cmake-modules/archive/refs/heads/main.zip"
    DOWNLOAD_NO_PROGRESS TRUE
    )

FetchContent_MakeAvailable(cmake-modules)

fetch_glow(
    VERSION
    "next"
    )

fetch_clap(
    VERSION
    "main"
    )

fetch_clap_helpers(
    VERSION
    "main"
    )

fetch_clap_wrapper(
    VERSION
    "main"
    )
