@echo off
echo Compiling Library System...
g++ -std=c++11 -Isrc main.cpp src/Book.cpp src/User.cpp src/Library.cpp src/Login.cpp src/AdminMenu.cpp src/UserMenu.cpp -o library_system.exe

if exist library_system.exe (
    echo.
    echo Running program...
    echo.
    library_system.exe
) else (
    echo Compilation failed!
)
pause
