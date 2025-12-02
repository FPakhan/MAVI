#include "Enemigo.h"

void Enemigo::iniciar(Vector2 pos, float esc, float i, float d) {
    sprite = LoadTexture("assets/enemigo.png");

    posicion = pos;
    escala = esc;
    ancho = sprite.width * escala;
    alto = sprite.height * escala;

    limIzq = i;
    limDer = d;

    velocidad = 2;
}

void Enemigo::actualizar() {
    posicion.x += velocidad;
    if (posicion.x < limIzq || posicion.x > limDer)
        velocidad = -velocidad;
}

void Enemigo::dibujar() {
    DrawTextureEx(sprite, posicion, 0, 0.2f, WHITE);
}

Rectangle Enemigo::getRect() {
    return { posicion.x, posicion.y, ancho, alto };
}
