@echo off
echo Building the project...
cmake --build . --config Release
if %errorlevel% equ 0 (
    echo Build successful! Running the executable...
    echo.
    .\Release\test.exe
) else (
    echo Build failed!
    pause
)