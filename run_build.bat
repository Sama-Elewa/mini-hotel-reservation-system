@echo off
cd /d "%~dp0"

rmdir /s /q build

cmake -S . -B build -G "MinGW Makefiles" ^
-DCMAKE_PREFIX_PATH="G:\Program-files-OLD\QT\6.10.2\mingw_64\lib\cmake"

cmake --build build

G:\Program-files-OLD\QT\6.10.2\mingw_64\bin\windeployqt.exe build\appGUI.exe

build\appGUI.exe
pause