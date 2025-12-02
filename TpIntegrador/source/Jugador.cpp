#include "Jugador.h"

void Jugador::iniciar(Vector2 pos, float esc) {
    sprite = LoadTexture("assets/jugador.png");

    escala = esc;
    ancho = sprite.width * escala;
    alto = sprite.height * escala;

    posicion = pos;
    velocidad = { 0,0 };
    enSuelo = false;
}

void Jugador::actualizar(Rectangle piso, Rectangle pBaja, Rectangle pAlta) {
    mover();
    aplicarGravedad();

    // Colisiones
    chequearColision(piso);
    chequearColision(pBaja);
    chequearColision(pAlta);
}

void Jugador::mover() {
    if (IsKeyDown(KEY_RIGHT)) posicion.x += 4;
    if (IsKeyDown(KEY_LEFT))  posicion.x -= 4;

    if (IsKeyPressed(KEY_SPACE) && enSuelo) {
        velocidad.y = -12;
        enSuelo = false;
    }
}

void Jugador::aplicarGravedad() {
    velocidad.y += 0.6f;
    posicion.y += velocidad.y;
}

void Jugador::chequearColision(Rectangle p) {
    Rectangle r = getRect();

    if (CheckCollisionRecs(r, p)) {
        if (velocidad.y > 0) {
            posicion.y = p.y - alto;
            velocidad.y = 0;
            enSuelo = true;
            
        }
    }
}



void Jugador::dibujar() {
    DrawTextureEx(sprite, posicion, 0, 0.2f, WHITE);
}

Rectangle Jugador::getRect() {
    return { posicion.x, posicion.y, ancho, alto };
}
