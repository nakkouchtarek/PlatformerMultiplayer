clang src/*.c -I %CD%\include -I %CD%\..\SDL_64\include -L %CD%\..\SDL_64\lib -o %CD%\bin\main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lWs2_32
%CD%\bin\main.exe