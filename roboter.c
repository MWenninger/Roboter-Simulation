// Funktionen zur Bewegung des Roboters //

#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "roboter.h"

void Roboter_Bewegung(struct roboter *roboter_werte,
                        struct SetUp *SetUpVariablen) {

    // Tasten Abrafragen + Bewegung //
    double alte_x = roboter_werte->x;
    double alte_y = roboter_werte->y;
    double bewegung_x;
    double bewegung_y;

    // Geschwindigkeitsabfrage
    if (IsKeyDown(KEY_RIGHT_SHIFT)) {
        roboter_werte->geschwindigkeit = 400;
    } else  { roboter_werte->geschwindigkeit = 300;
    }

    roboter_werte->akkuVerbrauchProPixel = 
        roboter_werte->geschwindigkeit * roboter_werte->akkuFaktor;
    
    double bewegung = 
        roboter_werte->geschwindigkeit * GetFrameTime();

    // Position verändern
    if (IsKeyDown(KEY_UP) && roboter_werte->akku > 0) {
        roboter_werte->y =  roboter_werte->y - bewegung;
        //roboter_werte->akku = roboter_werte->akku - bewegung * roboter_werte->akkuVerbrauchProPixel;
    }
    if (IsKeyDown(KEY_DOWN) && roboter_werte->akku > 0) {
        roboter_werte->y =  roboter_werte->y + bewegung;
        //roboter_werte->akku = roboter_werte->akku - bewegung * roboter_werte->akkuVerbrauchProPixel;
    }
    if (IsKeyDown(KEY_LEFT) && roboter_werte->akku > 0) {
        roboter_werte->x =  roboter_werte->x - bewegung;
        //roboter_werte->akku = roboter_werte->akku - bewegung * roboter_werte->akkuVerbrauchProPixel;
    }
    if (IsKeyDown(KEY_RIGHT) && roboter_werte->akku > 0) {
        roboter_werte->x =  roboter_werte->x + bewegung;
        //roboter_werte->akku = roboter_werte->akku - bewegung * roboter_werte->akkuVerbrauchProPixel;
    }

    // Roboter begrenzen
    if (roboter_werte->x < 0) {
        roboter_werte->x = 0;
    }
     if (roboter_werte->x + roboter_werte->breiteHitBox > SetUpVariablen->fensterBreite) {
        roboter_werte->x = SetUpVariablen->fensterBreite - roboter_werte->breiteHitBox;
    } 
    if (roboter_werte->y < 0) {
        roboter_werte->y = 0;
    } 
    if (roboter_werte->y + roboter_werte->höheHitBox > SetUpVariablen->fensterHöhe) {
        roboter_werte->y = SetUpVariablen->fensterHöhe - roboter_werte->höheHitBox;
    }

    // Physische Bewegung berechnen
    bewegung_x = roboter_werte->x - alte_x;
    bewegung_y = roboter_werte->y - alte_y;

    double strecke;
    strecke = sqrt(
        bewegung_x * bewegung_x + bewegung_y * bewegung_y);

    // Akku Verbrauch berechnen
        roboter_werte->akku = 
            roboter_werte->akku - strecke * roboter_werte->akkuVerbrauchProPixel;
    
    // Akku Stand begrenzen nach unten
    if (roboter_werte->akku < 0) {
    roboter_werte->akku = 0;
    }
}


// lokale Variablen für "Roboter_Laden"
double ladeStart = 0;
double ladezeit;

void Roboter_Laden (struct roboter *roboter_werte,
                    struct ladestation *ladestation_werte) {

    //ladestation_werte->aufLadestation = false; (wird nicht benötigt?)
    
    // Prüfen, ob Roboter Ladestation berührt
    if (roboter_werte->x < ladestation_werte->x + 110 &&
        roboter_werte->x + roboter_werte->breiteHitBox > ladestation_werte->x &&
        roboter_werte->y < ladestation_werte->y + 110 &&
        roboter_werte->y + roboter_werte->höheHitBox > ladestation_werte->y) {

            if (ladestation_werte->aufLadestation == false) {
                ladeStart = GetTime();
                ladestation_werte->aufLadestation = true;
            }

            ladezeit = GetTime() - ladeStart;

        } else {
            ladestation_werte->aufLadestation = false;
            ladezeit = 0;
        }

        // Akku hinzufügen
        if (ladezeit > 0.5) {
            roboter_werte->akku = roboter_werte->akku + ladezeit * ladestation_werte->akkuLadeFaktor;
        }

        // Akku begrenzen nach oben
        if (roboter_werte->akku >= 100) {
        roboter_werte->akku = 100;
        }
}

enum roboter_status RoboterStatusPrüfen(struct roboter *roboter_werte,
                    struct ladestation *ladestation_werte) {
    if (roboter_werte->akku <= 0) {
        return AKKU_LEER;
    }

    if (ladestation_werte->aufLadestation == true && roboter_werte->akku < 100) {
        return LADEN;
    }

    return NORMAL;
    
}