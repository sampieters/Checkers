//  Student: Sam Pieters
//  Rolnummer: s0191363
//  Opmerkingen: Alle opdrachten behalve schaakmat, pad en open zijn geimplementeerd
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H
#include "SchaakStuk.h"

class Game {
// variabelen om de status van het spel/bord te bewaren
public:
    Game();
    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k
    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();

    SchaakStuk* getPiece(int r, int k) {return bord[r][k];}
    void setPiece(int r, int k, SchaakStuk* s) {bord[r][k] = s;
    if (s != nullptr) {s->setPosition(pair<int, int> (r, k));}}
    void setStartBord(int r, int k, SchaakStuk* s) {bord[r][k] = s;}

private:
    SchaakStuk* bord[8][8];
};

#endif //SCHAKEN_GAME_H
