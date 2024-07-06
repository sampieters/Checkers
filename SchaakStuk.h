//  Student: Sam Pieters
//  Rolnummer: s0191363
//  Opmerkingen: Alle opdrachten behalve schaakmat, pad en open zijn geimplementeerd
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <chessboard.h>
using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:
    SchaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Deze functie krijg je cadeau
                                        // Je hebt die nodig om het stuk in de
                                        // GUI te tekenen
                                        // Meer info: kijk naar mainwindow.cpp, lijn 27

    zw getKleur() const { return kleur; }

    virtual vector<pair<int,int>> geldige_zetten(Game& g);
    pair<int,int> getPosition() {return position;};
    void setPosition(pair<int, int> set);

private:
    zw kleur;
    pair<int,int> position;
};


class Pion:public SchaakStuk {
public:
    explicit Pion(zw kleur):SchaakStuk(kleur) {}
    Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};



class Toren:public SchaakStuk {
public:
    explicit Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Paard:public SchaakStuk {
public:
    explicit Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Loper:public SchaakStuk {
public:
    explicit Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Koning:public SchaakStuk {
public:
    explicit Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Koningin:public SchaakStuk {
public:
    explicit Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

#endif //SCHAKEN_SCHAAKSTUK_H
