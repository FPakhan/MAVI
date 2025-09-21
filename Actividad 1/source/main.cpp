#ifndef NDEBUG
#include <vld.h> 
#endif

#include "raylib.h"

int main(void){
    
    InitWindow(800, 450, "Francisco Viñabal");

    
    SetTargetFPS(60);

    Color fondo = { 110, 100, 215, 255 };
    Color texto = LIGHTGRAY;
    Color Circulo = GREEN;

    
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(fondo);
        DrawText("Leandro Francisco Viñabal", 90, 200, 20, texto);
        DrawCircle(90, 50, 30, Circulo);
        if (IsKeyPressed(KEY_SPACE)) {
            texto = RED;
            Circulo = RED;
        }
        EndDrawing();


    }

 
    CloseWindow();

    return 0;
}

