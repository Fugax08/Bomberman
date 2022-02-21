clang -o parse_bmp.exe -I .\SDL2-2.0.20\include -L .\SDL2-2.0.20\lib\x64 .\parse_bmp.c -Xlinker /subsystem:console -lSDL2main -lSDL2 -lshell32
parse_bmp.exe
