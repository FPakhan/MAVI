#ifndef NDEBUG
#include <vld.h> 
#endif

#include "raylib.h"

int main(void){
    
    InitWindow(1024, 768, "Francisco Viñabal");
    SetTargetFPS(60);
    InitAudioDevice(); //activo el sonido 

    // Datos del botón
    Vector2 botonCentro = { 1024 - 60, 60 };  // esquina superior derecha
    float botonRadio = 40;

    // Colores de fondo
    Color fondo1 = RAYWHITE;
    Color fondo2 = LIGHTGRAY;
    bool usarFondo2 = false;

    //Cargo las texturas
    Texture2D textura1 = LoadTexture("sprite.png");
    // Les pongo filtro bilinear
    SetTextureFilter(textura1, TEXTURE_FILTER_BILINEAR);
   
    //Posicion de las texturas 
    Vector2 postex1 = { 350,250 };
    
    //Establesco la velocidad
    float movtex = 200.0f;
    float altura = 150;
    float suelo = 250;
    bool subiendo = false;
    bool bajando = false;
    const char* textoTecla = "Ninguna tecla"; // puntero a texto actual 
    bool mostrarMensaje = false; // controla si el mensaje está visible

    //Cargo el sonido
    Sound saltoSound = LoadSound("salto.mp3");



    while (!WindowShouldClose()){
        BeginDrawing();
        
        if (usarFondo2)
            ClearBackground(fondo2);
        else
            ClearBackground(fondo1);


        Vector2 mouse = GetMousePosition();

        // Detectar clic dentro del botón circular
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointCircle(mouse, botonCentro, botonRadio)) {
            usarFondo2 = !usarFondo2;  // Alterna el color del fondo
        }


        //Les doy control a los sprites
        if (IsKeyPressed(KEY_R)) {
            postex1 = { 350,250 };
        }
        if (IsKeyDown(KEY_RIGHT)) {
            postex1.x += movtex * GetFrameTime();
        }
        if (IsKeyDown(KEY_LEFT)) {
            postex1.x -= movtex * GetFrameTime();
        }
        if (IsKeyPressed(KEY_SPACE) && !subiendo && !bajando) {
            subiendo = true;
            PlaySound(saltoSound);
        }
        if (subiendo) {
            postex1.y -= (movtex+100.0f)* GetFrameTime();
            if (postex1.y <= altura) {
                postex1.y = altura;
                subiendo = false;
                bajando = true;
            }
        }
        
        if (bajando) {
            postex1.y += movtex * GetFrameTime();
            if (postex1.y >= suelo) {
                postex1.y = suelo;
                bajando = false;
            }
        } 
        // Detectar qué tecla está presionada
        if (IsKeyDown(KEY_SPACE)) textoTecla = "Espacio";
        else if (IsKeyDown(KEY_LEFT)) textoTecla = "Flecha izquierda";
        else if (IsKeyDown(KEY_RIGHT)) textoTecla = "Flecha derecha";
        else if (IsKeyDown(KEY_UP)) textoTecla = "Flecha arriba";
        else if (IsKeyDown(KEY_DOWN)) textoTecla = "Flecha abajo";
        else if (IsKeyDown(KEY_R)) textoTecla = "Tecla R";
        else if (IsKeyDown(KEY_M)) textoTecla = "Tecla M";
        else textoTecla = "Ninguna tecla";
        
        if (IsKeyPressed(KEY_M)) {
            mostrarMensaje = !mostrarMensaje; // cambia entre true/false
        }
        
        
        DrawTextureEx(textura1, postex1, 0.0f, 0.5f, WHITE);
        
        

        DrawText("Maguito ", 150, 600, 20,BLACK);
        DrawText(TextFormat("Posicion del mago:  (%.1f, %.1f)", postex1.x,postex1.y), 150, 620, 20, BLACK);
        DrawText("Color: Blanco ", 150, 640, 20, BLACK);
        DrawText(TextFormat("Tecla presionada: %s", textoTecla), 150,660, 20, BLACK);
        DrawText("Posicion del mouse: ", 150, 680, 20, BLACK);
        DrawText(TextFormat("X: %.2f", mouse.x), 150, 700, 20, BLACK);
        DrawText(TextFormat("Y: %.2f", mouse.y), 150, 720, 20, BLACK);

        // Dibujar el botón rojo
        DrawCircleV(botonCentro, botonRadio, RED);
        if (mostrarMensaje) {
            DrawText("Hechizo de salto activado!(presiona M para ocultar)", 150, 680, 20, BLACK);
        }
        EndDrawing();


    }

    //Liberacion de recursos 
    UnloadTexture(textura1);
    CloseWindow();
    CloseAudioDevice();

    return 0;
}

