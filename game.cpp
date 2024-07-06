//  Student: Sam Pieters
//  Rolnummer: s0191363
//  Opmerkingen: Alle opdrachten behalve schaakmat, pad en open zijn geimplementeerd
//

#include "game.h"
#include <iostream>
#include <algorithm>

Game::Game() {}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {
    Game::setPiece(7,0, new Toren(wit));
    Game::setPiece(7,1, new Paard(wit));
    Game::setPiece(7,2, new Loper(wit));
    Game::setPiece(7,3, new Koningin(wit));
    Game::setPiece(7,4, new Koning(wit));
    Game::setPiece(7,5, new Loper(wit));
    Game::setPiece(7,6, new Paard(wit));
    Game::setPiece(7,7, new Toren(wit));
    Game::setPiece(0,0, new Toren(zwart));
    Game::setPiece(0,1, new Paard(zwart));
    Game::setPiece(0,2, new Loper(zwart));
    Game::setPiece(0,3, new Koningin(zwart));
    Game::setPiece(0,4, new Koning(zwart));
    Game::setPiece(0,5, new Loper(zwart));
    Game::setPiece(0, 6, new Paard(zwart));
    Game::setPiece(0, 7, new Toren(zwart));
    for (int i = 0; i < 8; ++i) {
        Game::setPiece(6, i, new Pion(wit));
        Game::setPiece(1, i, new Pion(zwart));
    }
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            Game::setPiece(i, j, nullptr);}
    }}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    pair<int, int> current(r, k);
    for (int i=0; i < s->geldige_zetten(*this).size(); i++) {
        if (current == s->geldige_zetten(*this)[i]) {
            bord[s->getPosition().first][s->getPosition().second] = nullptr;
            s->setPosition(current);
            bord[r][k] = s;
            return true;}}
    return false;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    SchaakStuk *koning = nullptr;
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            if (getPiece(i, j) != nullptr and getPiece(i, j)->piece().type() == Piece::King) {
                if (kleur == wit) {
                    if (getPiece(i, j)->piece().color() == Piece::White) {
                        koning = getPiece(i, j);
                        break;}}

                else {
                    if (getPiece(i, j)->piece().color() == Piece::Black) {
                        koning = getPiece(i, j);
                        break;}}}}

        if (koning != nullptr) {break;}}

    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            if (getPiece(i, j) != nullptr) {
                if (!getPiece(i, j)->geldige_zetten(*this).empty()) {
                    for (int k = 0; k <= getPiece(i, j)->geldige_zetten(*this).size(); ++k) {
                        if (getPiece(i, j)->geldige_zetten(*this)[k] == koning->getPosition() and
                            getPiece(i, j)->getKleur() != kleur) {
                            return true;
                        }}}}}}
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    SchaakStuk *koning = nullptr;
    vector<pair<int, int>> checked;
    vector<pair<int, int>> pakken;
    pair<int, int> pak;
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            if (getPiece(i, j) != nullptr and getPiece(i, j)->piece().type() == Piece::King) {
                if (kleur == wit) {
                    if (getPiece(i, j)->piece().color() == Piece::White) {
                        koning = getPiece(i, j);
                        break;
                    }}

                else {
                    if (getPiece(i, j)->piece().color() == Piece::Black) {
                        koning = getPiece(i, j);
                        break;
                    }}}}
        if (koning != nullptr) {break;}}

    // Als de koning zijn zetten in de geldige zetten van een schaakstuk zitten van een andere kleur
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            // Als het vakje een schaakstuk bevat
            if (getPiece(i, j) != nullptr) {
                // Als het schaakstuk een andere kleur heeft en de geldige zetten van een schaakstuk niet leeg is
                if (!getPiece(i, j)->geldige_zetten(*this).empty() and getPiece(i, j)->getKleur() != koning->getKleur()) {
                    // kijk in alle geldige zetten van het schaakstuk
                    for (int k = 0; k < getPiece(i, j)->geldige_zetten(*this).size(); ++k) {
                        // check of in een schaakstuk zijn geldige zetten de koning zijn geldige zetten zit
                        for (int l = 0; l < checked.size(); ++l) {
                            if (checked[l] == getPiece(i, j)->geldige_zetten(*this)[k] and getPiece(i, j) != koning) {
                                // Hier nog een delete van een bepaald element maar ken de voc daar ni van
                                pak.first = i;
                                pak.second = j;
                                pakken = getPiece(i, j)->geldige_zetten(*this);
                                checked.erase(remove(checked.begin(), checked.end(), checked[l]), checked.end());
                        }}}}}}}

    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            if (getPiece(i, j) != nullptr) {
                // Als het schaakstuk eenwelfde kleur heeft en de geldige zetten van een schaakstuk niet leeg is
                if (!getPiece(i, j)->geldige_zetten(*this).empty() and getPiece(i, j)->getKleur() == koning->getKleur()) {
                    // Kijk dan of die zijn geldige zetten in pakken zit, als dat is dan kan een stuk nog de schaakmat oplossen
                    for (int k = 0; k < getPiece(i, j)->geldige_zetten(*this).size(); ++k) {
                        // check of in een schaakstuk zijn geldige zetten de koning zijn geldige zetten zit
                        if (getPiece(i, j)->geldige_zetten(*this)[k] == pak) {
                            return false;
                        }
                        for (int l = 0; l < pakken.size(); ++l) {
                            if (pakken[l] == getPiece(i, j)->geldige_zetten(*this)[k] and getPiece(i, j) != koning) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return checked.empty();
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}

