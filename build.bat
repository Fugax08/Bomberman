clang -o bomberman.exe -I .\SDL2-2.0.20\include -L .\SDL2-2.0.20\lib\x64 .\bomberman.c -Xlinker /subsystem:console -lSDL2main -lSDL2 -lshell32

bomberman.exe