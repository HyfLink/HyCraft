call "vendor/premake5/premake5.exe" gmake
if "%1" == "release" (
    call "make" -C build config=release all
) else (
    call "make" -C build config=debug all
)
