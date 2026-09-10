#include <stdio.h>
#include "raylib.h"
#include "roboter.h"
#include <stdbool.h>

// Setup //
int main(void) {

// Setup Variablen
struct SetUp SetUpVariablen;
SetUpVariablen.fensterBreite = 1000;
SetUpVariablen.fensterHöhe = 700;

printf("%f",GetFrameTime());

InitWindow(SetUpVariablen.fensterBreite, SetUpVariablen.fensterHöhe, "Roboterhund Simulation");
SetTargetFPS(40);


// Roboter erstellen
struct roboter roboter_werte;
// Startwerte Roboter
roboter_werte.x = 450;
roboter_werte.y = 300;
roboter_werte.breiteHitBox = 50;
roboter_werte.höheHitBox = 83;
roboter_werte.geschwindigkeit = 300;
roboter_werte.akku = 100.00;
roboter_werte.akkuFaktor = 0.00004;
roboter_werte.akkuVerbrauchProPixel = roboter_werte.geschwindigkeit * roboter_werte.akkuFaktor; 
            /* Bsp.: akkuVerbrauchProPixel = 300 × 0.0001 = 0.03 -> 0.03 Akku Einheiten/Pixel */
roboter_werte.status = NORMAL;

// Ladestation erstellen
struct ladestation ladestation_werte;
// Startwerte Ladestation
ladestation_werte.x = 0;
ladestation_werte.y = 590;
ladestation_werte.akkuLadeFaktor = 0.5;

enum roboter_status status;
// (in weil schleife packen) ->  status = RoboterStatusPrüfen(&roboter_werte, &ladestation_werte);


Texture2D roboterBild = LoadTexture("Roboter.png");

while (!WindowShouldClose()) {

    // Roboter bewegen //
    Roboter_Bewegung(&roboter_werte, &SetUpVariablen);

    // Roboter Laden //
    Roboter_Laden(&roboter_werte, &ladestation_werte);

    // Drawings //
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("ROBOTERHUND SIMULATION", 300, 50, 30, BLACK);

    DrawRectangle((int)ladestation_werte.x, (int)ladestation_werte.y, 110, 110, GREEN);


    /* Nur für Test Zwecke (macht Hitbox sichtbar)
    DrawRectangleLines(
    (int)roboter_werte.x,
    (int)roboter_werte.y,
    (int)roboter_werte.breiteHitBox,
    (int)roboter_werte.höheHitBox,
    RED
     ); */

    Vector2 positionRoboter = { roboter_werte.x, roboter_werte.y };
    DrawTextureEx(roboterBild, positionRoboter, 0.0f,  0.1f, RED);

    DrawText(TextFormat("Akku: %.2f %%", roboter_werte.akku), 10, 10, 20, BLUE);

    EndDrawing();
}

UnloadTexture(roboterBild);

CloseWindow();

return 0;

}
