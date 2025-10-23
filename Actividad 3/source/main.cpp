#ifndef NDEBUG
#include <vld.h> 
#endif

#include "raylib.h"

int main(void){
    
    InitWindow(1024, 768, "Francisco Viñabal");
    SetTargetFPS(60);

    //Cargo las texturas
    Texture2D textura1 = LoadTexture("sprite.png");
    Texture2D textura2 = LoadTexture("sprite2.png");
    // Les pongo filtro bilinear
    SetTextureFilter(textura1, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(textura2, TEXTURE_FILTER_BILINEAR);
    //Posicion de las texturas 
    Vector2 postex1 = { 50,100 };
    Vector2 postex2 = { 700,200 };
    Vector2 postemp;
    //Calculo la escala
    float escalaX, escalaY;
    float height_tex1 = (float)textura1.height;
    float width_tex1 = (float)textura1.width;
    float height_tex2 = (float)textura2.height;
    float width_tex2 = (float)textura2.width;
  
    escalaX = height_tex1 / height_tex2;
    escalaY = width_tex1 / width_tex2;
    
    float escala1= escalaX - 0.5;
    float escala2 = escalaX - 0.7;
    //Establesco la velocidad
    float movtex = 200.0f;
    //Defino los colores
    Color Ctex1 = { 188,10,150,255 };
    Color Ctex2 = { 18,150,50,255 };
 

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        //Les doy control a los sprites
        if (IsKeyDown(KEY_RIGHT)) {
            postex1.x += movtex * GetFrameTime();
        }
        if (IsKeyDown(KEY_LEFT)) {
            postex1.x -= movtex * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN)){
            postex2.y += movtex * GetFrameTime();
        }  
        if (IsKeyDown(KEY_UP)){
            postex2.y -= movtex * GetFrameTime();
        }
        //Cambio los sprites de propiedades
        if (IsKeyPressed(KEY_SPACE)){
            float escalatemp = escala1;
            escala1 = escala2;
            escala2 = escalatemp;

            Ctex1= { 18,150,50,255 };
            Ctex2= { 188, 10, 150, 255 };

            postemp = postex1;
            postex1 = postex2;
            postex2 = postemp;

        }
        //Dibujo los sprites
        DrawTextureEx(textura1, postex1, 0.0f, escala1, Ctex1);
        DrawTextureEx(textura2, postex2, 0.0f, escala2, Ctex2);
        //Describo sus propiedades
        DrawText("Sprite 1", 150, 400, 20,BLACK);
        DrawText(TextFormat("Escala: %.2f",escala1) , 150, 420, 20, BLACK);
        DrawText(TextFormat("Posicion:  (%.1f, %.1f)", postex1.x,postex1.y), 150, 440, 20, BLACK);
        DrawText("Color: Blanco ", 150, 460, 20, BLACK);


        DrawText("Sprite 2", 650, 400, 20, BLACK);
        DrawText(TextFormat("Escala: %.2f", escala2), 650, 420, 20, BLACK);
        DrawText(TextFormat("Posicion:  (%.1f, %.1f)", postex2.x, postex2.y), 650, 440, 20, BLACK);
        DrawText("Color: Verde ", 650, 460, 20, BLACK);







        EndDrawing();


    }

    //Liberacion de recursos 
    UnloadTexture(textura1);
    UnloadTexture(textura2);
    CloseWindow();

    return 0;
}

