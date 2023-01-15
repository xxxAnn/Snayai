@if not exist "./build" (
    @mkdir build >nul
)
@g++ -o build/snayai.exe -Wl,-Bstatic external/* src/* -Wl,--as-needed -ID:\Documents\Code\Personal\SFML\include >nul
@cp -fr ./external/* ./build