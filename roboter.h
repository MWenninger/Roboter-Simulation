#include <stdbool.h>

struct SetUp {
    int fensterBreite;
    int fensterHöhe;
};

enum roboter_status {
    NORMAL,
    LADEN,
    AKKU_LEER
};

struct roboter {
    double x;
    double y;
    double breiteHitBox;
    double höheHitBox;
    double geschwindigkeit; //Pixel/Sekunde
    double akku;
    double akkuFaktor;
    double akkuVerbrauchProPixel; // (geschwindigkeit * ...)
    double richtung;

    enum roboter_status status;
};

struct ladestation {
    double x;
    double y;
    double akkuLadeFaktor;
    bool aufLadestation;
};


void SetUp_Variablen(struct SetUp *SetUpVariablen);

void Roboter_Bewegung(struct roboter *roboter_werte,
                      struct SetUp *SetUpVariablen);

//void Roboter_Bildschirm_Begrenzung(struct roboter *roboter_werte);

//void Roboter_Laden(struct ladestation *ladestation_werte);

void Roboter_Laden(struct roboter *roboter_werte,
                   struct ladestation *ladestation_werte);

void Roboter_Zustand(struct roboter *roboter_werte,
                    struct ladestation *ladestation_werte);
                    