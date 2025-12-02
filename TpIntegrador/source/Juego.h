#pragma once
#include "raylib.h"
#include "Jugador.h"
#include "Enemigo.h"

enum Estado {
    MENU,
    JUGANDO,
    MUERTO,
    VICTORIA
};

class Juego {
public:
    Juego();
    void actualizar();
    void dibujar();

private:
    Estado estado;

    Jugador jugador;
    Enemigo enemigo;
    Enemigo enemigo2;

    // Plataformas
    Rectangle piso;
    Rectangle plataformaBaja;
    Rectangle plataformaAlta;
    Rectangle puerta;
    Rectangle botonIniciar;
    Rectangle botonSalir;
    

    // Fondo
    Vector2 circulos[25];
    float radios[25];
    Color colores[25];

    void actualizarMenu();
    void actualizarJuego();
    void actualizarMuerte();
    void actualizarVictoria();

    void dibujarMenu();
    void dibujarJuego();
    void dibujarMuerte();
    void dibujarVictoria();
};
