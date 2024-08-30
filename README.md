# Screen Saver using C and SDL2

Universidad del Valle de Guatemala, August 2024. <br>
Computación Paralela y Distribuida. <br>

Done by: <br>
- Javier Alejandro Azurdia Arrecis, 21242 <br>
- Diego Alejandro Morales Escobar, 21146 <br>
- Angel Sebastian Castellanos Pineda, 21700 <br>

---
## Description
bla bla bla bla

---
## How to run

Before actually running the code, you need to make sure that you have installed SDL2 in your machine. 
You can use the following guide to install it in your machine: [SDL2 Installation Guide](https://www.youtube.com/watch?v=N5CZLSVU0DA). Note that the cmake_modules folder is already added with its respective FindSDL2.cmake file, so you don't need to worry about it.

Also, the file SDL2.dll is already included into cmake-build-debug folder, so you don't need to worry about it. However, you must change the path in this instruction on the CMakeLists.txt file to the path where you have installed SDL2 in your machine.

```cmake
set(SDL2_PATH "C:/coding/CP/SDL2-devel-2.30.6-mingw/SDL2-2.30.6/x86_64-w64-mingw32")
```


---

Para correr esto, compilar el tonoto este con clion y despues en la carpeta cmake-build-debug correr el ejecutable que se genere.

```bash
cd /coding/CP/screensaver-p1/cmake-build-debug>
./screensaver_p1.exe 20 20
```


