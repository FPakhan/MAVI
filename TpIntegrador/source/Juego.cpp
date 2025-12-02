#include "Juego.h"

// CONSTRUCTOR
Juego::Juego() {

    estado = MENU;

    // Piso
    piso = { 0, 688, 1024, 80 };

    // Plataforma BAJA (grande)
    plataformaBaja = { 200, 560, 500, 40 };

    // Plataforma ALTA (chica)
    plataformaAlta = { 320, 420, 260, 40 };

    // Puerta final
    puerta = { 880, 608, 60, 80 };

    // Jugador
    jugador.iniciar({ 120, 640 }, 0.15f); // ESCALA del sprite = 0.15

    // Enemigo
    enemigo.iniciar({ 400, 620 }, 0.15f, 300, 600); // límite izq, der
    enemigo2.iniciar({ 400, 460 }, 0.1f, 300, 600);
    // Botones
    botonIniciar = { 412, 250, 200, 60 };
    botonSalir = { 412, 350, 200, 60 };
   
    // Fondo
    for (int i = 0; i < 25; i++) {
        circulos[i] = { (float)GetRandomValue(0, 1024), (float)GetRandomValue(0, 768) };
        radios[i] = (float)GetRandomValue(30, 90);
        colores[i] = { (unsigned char)GetRandomValue(150, 220),
                       (unsigned char)GetRandomValue(150, 220),
                       (unsigned char)GetRandomValue(200, 255),
                       (unsigned char)GetRandomValue(40, 90) };
    }
}


// ACTUALIZAR

void Juego::actualizar() {
    switch (estado) {
    case MENU:     actualizarMenu();     break;
    case JUGANDO:  actualizarJuego();    break;
    case MUERTO:   actualizarMuerte();   break;
    case VICTORIA: actualizarVictoria(); break;
    }
}


// DIBUJAR

void Juego::dibujar() {
    switch (estado) {
    case MENU:     dibujarMenu();     break;
    case JUGANDO:  dibujarJuego();    break;
    case MUERTO:   dibujarMuerte();   break;
    case VICTORIA: dibujarVictoria(); break;
    }
}


// ACTUALIZAR ESTADOS


void Juego::actualizarMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        estado = JUGANDO;
    }

}

void Juego::actualizarJuego() {

    jugador.actualizar(piso, plataformaBaja, plataformaAlta);

    enemigo.actualizar();
    enemigo2.actualizar();

    // Colisión jugador–enemigo → muerte
    if (CheckCollisionRecs(jugador.getRect(), enemigo.getRect())) {
        estado = MUERTO;
        return;
    }

    if (CheckCollisionRecs(jugador.getRect(), enemigo2.getRect())) {
        estado = MUERTO;
        return;
    }


    // Puerta
    if (CheckCollisionRecs(jugador.getRect(), puerta)) {
        if (IsKeyPressed(KEY_E)) {
            estado = VICTORIA;
            return;
        }
    }
}

void Juego::actualizarMuerte() {
    if (IsKeyPressed(KEY_R)) {
        *this = Juego();
    }
}

void Juego::actualizarVictoria() {
    if (IsKeyPressed(KEY_R)) {
        *this = Juego();
    }
}


// DIBUJO ESTADOS


void Juego::dibujarMenu() {
    DrawText("Tp Integrador Francisco Viñabal ", 390, 150, 30, LIGHTGRAY);

    Vector2 mouse = GetMousePosition();
    bool hoverIniciar = CheckCollisionPointRec(mouse, botonIniciar);
    bool hoverSalir = CheckCollisionPointRec(mouse, botonSalir);

    DrawRectangleRec(botonIniciar, hoverIniciar ? LIGHTGRAY : GRAY);
    DrawText("INICIAR", 450, 270, 22, BLACK);

    DrawRectangleRec(botonSalir, hoverSalir ? LIGHTGRAY : GRAY);
    DrawText("SALIR", 460, 370, 22, BLACK);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (hoverIniciar) {
            estado = JUGANDO;
        }
    }
    if (hoverSalir && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            EndDrawing();
            CloseWindow();
        }
}

void Juego::dibujarJuego() {

    // Fondo
    for (int i = 0; i < 25; i++)
        DrawCircleV(circulos[i], radios[i], colores[i]);

    // Piso y plataformas
    DrawRectangleRec(piso, GRAY);
    DrawRectangleRec(plataformaBaja, GRAY);
    DrawRectangleRec(plataformaAlta, GRAY);

    DrawText("Presiona E en la puerta para ganar", 270, 100, 30, WHITE);
    DrawText(TextFormat("Posicion del personaje:  (%.1f, %.1f)", jugador.posicion.x, jugador.posicion.y), 50, 50, 20, WHITE );
    

    // Puerta
    DrawRectangleRec(puerta, BROWN);

    enemigo.dibujar();
    enemigo2.dibujar();
    jugador.dibujar();
}

void Juego::dibujarMuerte() {
    DrawText("PERDISTE", 300, 300, 60, RED);
    DrawText("Presiona R para reiniciar", 270, 400, 30, WHITE);
    DrawText("ESC para salir", 350, 450, 30, GRAY);
}

void Juego::dibujarVictoria() {
    DrawText("GANASTE!", 300, 300, 60, GREEN);
    DrawText("Presiona R para reiniciar", 270, 400, 30, WHITE);
    DrawText("ESC para salir", 350, 450, 30, GRAY);
}
