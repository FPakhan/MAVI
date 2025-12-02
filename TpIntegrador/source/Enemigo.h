#pragma once
#include "raylib.h"

class Enemigo {
public:
    void iniciar(Vector2 pos, float escalaSprite, float limiteIZQ, float limiteDER);
    void actualizar();
    void dibujar();
    Rectangle getRect();

private:
    Texture2D sprite;
    Vector2 posicion;
    float escala;
    float ancho, alto;

    float limIzq, limDer;
    float velocidad;
};
