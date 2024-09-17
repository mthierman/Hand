include(FetchContent)

FetchContent_Declare(
    mthierman_glow URL "https://github.com/mthierman/Glow/archive/refs/heads/next.zip"
    DOWNLOAD_NO_PROGRESS TRUE
    )

FetchContent_MakeAvailable(mthierman_glow)
