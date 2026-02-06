@echo off
echo Cleaning previous builds...
del *.o 2>nul
del *.exe 2>nul
del src\*.o 2>nul

echo.
echo Compiling Online Library System...
echo.

echo Compiling core files...
g++ -std=c++11 -Isrc -c src/Book.cpp -o Book.o
g++ -std=c++11 -Isrc -c src/User.cpp -o User.o
g++ -std=c++11 -Isrc -c src/Library.cpp -o Library.o
g++ -std=c++11 -Isrc -c src/Login.cpp -o Login.o
g++ -std=c++11 -Isrc -c src/AdminMenu.cpp -o AdminMenu.o
g++ -std=c++11 -Isrc -c src/UserMenu.cpp -o UserMenu.o

echo.
echo Compiling main program...
g++ -std=c++11 -Isrc -c main.cpp -o main.o

echo.
echo Linking all files...
g++ -std=c++11 -o library_system.exe main.o Book.o User.o Library.o Login.o AdminMenu.o UserMenu.o

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ===========================================
    echo COMPILATION SUCCESSFUL!
    echo ===========================================
    echo.
    echo To run the program, type: library_system.exe
    echo.
    echo Default Login Credentials:
    echo Admin: username=admin, password=admin123
    echo User:  username=john,  password=password123
    echo User:  username=jane,  password=password456
    echo.
) else (
    echo.
    echo ===========================================
    echo COMPILATION FAILED!
    echo Check the errors above.
    echo ===========================================
)

del *.o 2>nul
pause
