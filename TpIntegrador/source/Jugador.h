#pragma once
#include "raylib.h"

class Jugador {
public:
    void iniciar(Vector2 posicionInicial, float escalaSprite);
    void actualizar(Rectangle piso, Rectangle pBaja, Rectangle pAlta);
    void dibujar();
    Rectangle getRect();
    Vector2 posicion;

private:
    Texture2D sprite;
   
    Vector2 velocidad;

    float escala;
    float ancho;
    float alto;

    bool enSuelo;

    void aplicarGravedad();
    void mover();
    void chequearColision(Rectangle plataforma);
};
