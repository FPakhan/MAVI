#include "raylib.h"



// Pelota
Texture2D pelota;          
Vector2 posicionPelota;    
Vector2 velocidadPelota;   

float velocidadJuego = 1.0f;   //aumenta o reduce la velocidad del juego



void UpdateBall();     // Actualiza la lógica de la pelota
void DrawGame();       // Dibuja todo en pantalla



int main() {
  
    InitWindow(800, 600, "Pelotita Rebotando - Unidad 5");
    SetTargetFPS(60);

    pelota = LoadTexture("assets/pelota.png");

    // Colocar pelota en el centro
    posicionPelota = { 400, 300 };

    // Dirección inicial aleatoria
    velocidadPelota.x = GetRandomValue(-200, 200);
    velocidadPelota.y = GetRandomValue(-200, 200);

    
    while (!WindowShouldClose()) {

      
        if (IsKeyPressed(KEY_UP)) velocidadJuego += 0.5f;
        if (IsKeyPressed(KEY_DOWN)) velocidadJuego -= 0.5f;

        //limitado para que no sea muy lento o muy rápido
        if (velocidadJuego < 0.2f) velocidadJuego = 0.2f;
        if (velocidadJuego > 5.0f) velocidadJuego = 5.0f;

     
        UpdateBall();
        DrawGame();
    }

    
    UnloadTexture(pelota);
    CloseWindow();
    return 0;
}



void UpdateBall() {

    
    float dt = GetFrameTime();
    posicionPelota.x += velocidadPelota.x * dt * velocidadJuego;
    posicionPelota.y += velocidadPelota.y * dt * velocidadJuego;

    int ancho = 0.2f;
    int alto = 0.2f;

    // Rebote contra el borde izquierdo
    if (posicionPelota.x <= 0) {
        posicionPelota.x = 0;
        velocidadPelota.x *= -1;     // Rebote
    }

    // Rebote contra el borde derecho
    if (posicionPelota.x + ancho >= 700) {
        posicionPelota.x = 700 - ancho;
        velocidadPelota.x *= -1;
    }

    // Rebote contra arriba
    if (posicionPelota.y <= 0) {
        posicionPelota.y = 0;
        velocidadPelota.y *= -1;
    }

    // Rebote contra abajo
    if (posicionPelota.y + alto >= 500) {
        posicionPelota.y = 500 - alto;
        velocidadPelota.y *= -1;
    }
}



void DrawGame() {

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureEx(pelota,{ posicionPelota.x, posicionPelota.y },0.0f,0.2f, WHITE);

    // Dibujar velocidad en pantalla
    DrawText(TextFormat("Velocidad del juego: %.1f", velocidadJuego), 20, 20, 20, DARKGRAY);
    DrawText("Flecha ARRIBA = Aumentar velocidad", 20, 50, 20, GRAY);
    DrawText("Flecha ABAJO  = Disminuir velocidad", 20, 75, 20, GRAY);

    EndDrawing();
}
