@echo off
cd src 
g++ main.cpp -IC:\Users\elias\Desktop\engine\src -IC:\Users\elias\Desktop\engine\SDL2_32\include\SDL2 -LC:\Users\elias\Desktop\engine\src -LC:\Users\elias\Desktop\engine\SDL2_32\lib -w -Wl, -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lSDL2 -o ../bin/Game 
cd ..
