@if not exist "./build" (
    @mkdir build >nul
)
@g++ -o build/snayai.exe -Wl,-Bstatic external/sfml-graphics-2.dll external/sfml-system-2.dll external/sfml-window-2.dll src/main.cpp -Wl,--as-needed -ID:\Documents\Code\Personal\SFML\include >nul
@xcopy ./external/* ./build /y