#include "raylib.h"
#include "Juego.h"

int main() {
    InitWindow(1024, 768, "TP Integrador Francisco Viñabal ");
    SetTargetFPS(60);

    Juego juego;

    while (!WindowShouldClose()) {
        juego.actualizar();
        BeginDrawing();
        ClearBackground(BLACK);
        juego.dibujar();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
