#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"  

int main(void) {
    const int anchoVentana = 1024;
    const int altoVentana = 768;
    InitWindow(anchoVentana, altoVentana, "La Esfera Viajera");
    SetTargetFPS(60);
    Color fondo = WHITE;
    Color texto = BLACK;
    Vector2 posicionEsfera = { 0.0f, 0.0f }; // Posición inicial de la esfera (esquina superior izquierda)
    Vector2 velocidadEsfera = { 300.0f, 200.0f };// Velocidad inicial de la esfera (en píxeles por segundo)
    float radioEsfera = 15.0f;    // Radio de la esfera
    Color colorEsfera = { 0, 255, 255, 180 };// Color inicial de la esfera (celeste transparente)
    Color colores[4] = {  // Paleta de colores por los que irá cambiando al rebotar
        {255, 0, 200, 180},   
        {0, 255, 255, 180},   
        {255, 128, 0, 180},   
        {150, 0, 255, 180}    
    }; 
    int indiceColor = 0; // Índice para seleccionar el color actual de la esfera
    int rebotes = -4; // Contador de rebotes (inicia en -4 para compensar los primeros 4 rebotes iniciales)
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();  // deltaTime guarda el tiempo transcurrido entre frames
        // Actualiza la posición de la esfera según su velocidad
        posicionEsfera.x += velocidadEsfera.x * deltaTime;
        posicionEsfera.y += velocidadEsfera.y * deltaTime;
        // Rebote contra el borde superior
        if (posicionEsfera.y - radioEsfera <= 0) {
            posicionEsfera.y = radioEsfera;
            velocidadEsfera.y = -velocidadEsfera.y;
            indiceColor = (indiceColor + 1) % 4;
            colorEsfera = colores[indiceColor];
            rebotes++;
        }
        // Rebote contra el borde derecho
        if (posicionEsfera.x + radioEsfera >= anchoVentana) {
            posicionEsfera.x = anchoVentana - radioEsfera;
            velocidadEsfera.x = -velocidadEsfera.x;
            indiceColor = (indiceColor + 1) % 4;
            colorEsfera = colores[indiceColor];
            rebotes++;
        }
        // Rebote contra el borde inferior
        if (posicionEsfera.y + radioEsfera >= altoVentana) {
            posicionEsfera.y = altoVentana - radioEsfera;
            velocidadEsfera.y = -velocidadEsfera.y;
            indiceColor = (indiceColor + 1) % 4;
            colorEsfera = colores[indiceColor];
            rebotes++;
        }
        // Rebote contra el borde izquierdo
        if (posicionEsfera.x - radioEsfera <= 0) {
            posicionEsfera.x = radioEsfera;
            velocidadEsfera.x = -velocidadEsfera.x;
            indiceColor = (indiceColor + 1) % 4;
            colorEsfera = colores[indiceColor];
            rebotes++;
        }
        BeginDrawing();  
        ClearBackground(fondo);
        DrawCircle((int)posicionEsfera.x, (int)posicionEsfera.y, radioEsfera, colorEsfera);
        // Dibuja información adicional en pantalla
        DrawText(TextFormat("Posicion: (%.1f, %.1f)", posicionEsfera.x, posicionEsfera.y), 10, 600, 20, texto);
        DrawText(TextFormat("Resolucion: %dx%d", anchoVentana, altoVentana), 10, 625, 20, texto);
        DrawText(TextFormat("Rebotes: %d", rebotes), 10, 650, 20, texto);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}