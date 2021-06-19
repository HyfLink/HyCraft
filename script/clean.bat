call "vendor/premake5/premake5.exe" gmake
if ("%1" == "release") (
    call "make" -C build clean config=release
) else (
    call "make" -C build clean config=debug
)
