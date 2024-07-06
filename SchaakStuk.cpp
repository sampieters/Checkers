#include <iostream>
#include "chessboard.h"
//  Student: Sam Pieters
//  Rolnummer: s0191363
//  Opmerkingen: Alle opdrachten behalve schaakmat, pad en open zijn geimplementeerd
//

#include "SchaakStuk.h"
#include "game.h"

vector<pair<int, int>> SchaakStuk::geldige_zetten(Game &g) {
    vector<pair<int, int>> geldig;
    return geldig;}

void SchaakStuk::setPosition(pair<int, int> set) {position = set;}

vector<pair<int, int>> Pion::geldige_zetten(Game &g) {
    vector<pair<int, int>> geldig;
    if (SchaakStuk::getKleur() == wit) {
        pair<int, int> leftneighbour(Pion::getPosition().first-1, Pion::getPosition().second-1);
        pair<int, int> rightneighbour(Pion::getPosition().first-1, Pion::getPosition().second+1);
        pair<int, int> upneighbour(Pion::getPosition().first-1, Pion::getPosition().second);
        pair<int, int> upperneighbour(Pion::getPosition().first-2, Pion::getPosition().second);

        if (Pion::getPosition().first == 6) {
            if (g.getPiece(upneighbour.first, upneighbour.second) == nullptr) {
                geldig.push_back(upneighbour);
                if (g.getPiece(upperneighbour.first, upperneighbour.second) == nullptr) {
                    geldig.push_back(upperneighbour);
                }}
            if (g.getPiece(leftneighbour.first, leftneighbour.second) != nullptr) {
                if (g.getPiece(leftneighbour.first, leftneighbour.second)->getKleur() == zwart) {
                    geldig.push_back(leftneighbour);
                }}
            if (g.getPiece(rightneighbour.first, rightneighbour.second) != nullptr) {
                if (g.getPiece(rightneighbour.first, rightneighbour.second)->getKleur() == zwart) {
                    geldig.push_back(rightneighbour);
                }}}
        else {
            if (Pion::getPosition().first != 0) {
                if (g.getPiece(leftneighbour.first, leftneighbour.second) != nullptr) {
                    if (g.getPiece(leftneighbour.first, leftneighbour.second)->getKleur() == zwart) {
                        geldig.push_back(leftneighbour);
                    }}
                if (g.getPiece(rightneighbour.first, rightneighbour.second) != nullptr) {
                    if (g.getPiece(rightneighbour.first, rightneighbour.second)->getKleur() == zwart) {
                        geldig.push_back(rightneighbour);
                }}
                if (g.getPiece(upneighbour.first, upneighbour.second) == nullptr) {
                    geldig.push_back(upneighbour);
                    }}}}
    else {
        pair<int, int> leftneighbour(Pion::getPosition().first+1, Pion::getPosition().second+1);
        pair<int, int> rightneighbour(Pion::getPosition().first+1, Pion::getPosition().second-1);
        pair<int, int> upneighbour(Pion::getPosition().first+1, Pion::getPosition().second);
        pair<int, int> upperneighbour(Pion::getPosition().first+2, Pion::getPosition().second);
        if (SchaakStuk::getPosition().first == 1) {
            if (g.getPiece(upneighbour.first, upneighbour.second) == nullptr) {
                geldig.push_back(upneighbour);
                if (g.getPiece(upperneighbour.first, upperneighbour.second) == nullptr) {
                    geldig.push_back(upperneighbour);
                }}
            if (g.getPiece(leftneighbour.first, leftneighbour.second) != nullptr) {
                if (g.getPiece(leftneighbour.first, leftneighbour.second)->getKleur() == wit) {
                    geldig.push_back(leftneighbour);
                }}
            if (g.getPiece(rightneighbour.first, rightneighbour.second) != nullptr) {
                if (g.getPiece(rightneighbour.first, rightneighbour.second)->getKleur() == wit) {
                    geldig.push_back(rightneighbour);
                }}}
        else {
            if (Pion::getPosition().first != 7) {
                if (g.getPiece(leftneighbour.first, leftneighbour.second) != nullptr) {
                    if (g.getPiece(leftneighbour.first, leftneighbour.second)->getKleur() == wit) {
                        geldig.push_back(leftneighbour);
                    }}
                if (g.getPiece(rightneighbour.first, rightneighbour.second) != nullptr) {
                    if (g.getPiece(rightneighbour.first, rightneighbour.second)->getKleur() == wit) {
                        geldig.push_back(rightneighbour);
                    }}
                if (g.getPiece(upneighbour.first, upneighbour.second) == nullptr) {
                    geldig.push_back(upneighbour);
                }}}}
return geldig;
}

vector<pair<int, int>> Koning::geldige_zetten(Game &g) {
    vector<pair<int, int>> geldig;
    pair<int, int> leftneighbour(Koning::getPosition().first, Koning::getPosition().second-1);
    pair<int, int> rightneighbour(Koning::getPosition().first, Koning::getPosition().second+1);
    pair<int, int> upneighbour(Koning::getPosition().first+1, Koning::getPosition().second);
    pair<int, int> downneighbour(Koning::getPosition().first-1, Koning::getPosition().second);
    pair<int, int> upleftneighbour(Koning::getPosition().first-1, Koning::getPosition().second-1);
    pair<int, int> uprightneighbour(Koning::getPosition().first-1, Koning::getPosition().second+1);
    pair<int, int> downleftneighbour(Koning::getPosition().first+1, Koning::getPosition().second-1);
    pair<int, int> downrightneighbour(Koning::getPosition().first+1, Koning::getPosition().second+1);

    if (leftneighbour.second >= 0) {
        if (g.getPiece(leftneighbour.first, leftneighbour.second) != nullptr) {
            if (g.getPiece(leftneighbour.first, leftneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(leftneighbour);
            }
        } else {geldig.push_back(leftneighbour);}
    }
    if (upleftneighbour.first >= 0 and upleftneighbour.second >= 0) {
        if (g.getPiece(upleftneighbour.first, upleftneighbour.second) != nullptr) {
            if (g.getPiece(upleftneighbour.first, upleftneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(upleftneighbour);
            }
        } else { geldig.push_back(upleftneighbour); }
    }
    if (rightneighbour.second < 8) {
        if (g.getPiece(rightneighbour.first, rightneighbour.second) != nullptr) {
            if (g.getPiece(rightneighbour.first, rightneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(rightneighbour);
            }
        } else { geldig.push_back(rightneighbour); }
    }
    if (uprightneighbour.first >= 0 and uprightneighbour.second < 8) {
        if (g.getPiece(uprightneighbour.first, uprightneighbour.second) != nullptr) {
            if (g.getPiece(uprightneighbour.first, uprightneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(uprightneighbour);
            }
        } else { geldig.push_back(uprightneighbour); }
    }
    if (upneighbour.first < 8) {
        if (g.getPiece(upneighbour.first, upneighbour.second) != nullptr) {
            if (g.getPiece(upneighbour.first, upneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(upneighbour);
            }
        } else { geldig.push_back(upneighbour); }
    }
    if (downneighbour.first >= 0) {
        if (g.getPiece(downneighbour.first, downneighbour.second) != nullptr) {
            if (g.getPiece(downneighbour.first, downneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(downneighbour);
            }
        } else { geldig.push_back(downneighbour); }
    }
    if (downrightneighbour.first < 8 and downrightneighbour.second < 8) {
        if (g.getPiece(downrightneighbour.first, downrightneighbour.second) != nullptr) {
            if (g.getPiece(downrightneighbour.first, downrightneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(downrightneighbour);
            }
        } else { geldig.push_back(downrightneighbour); }
    }
    if (downleftneighbour.first < 8 and downleftneighbour.second >= 0) {
        if (g.getPiece(downleftneighbour.first, downleftneighbour.second) != nullptr) {
            if (g.getPiece(downleftneighbour.first, downleftneighbour.second)->getKleur() != SchaakStuk::getKleur()) {
                geldig.push_back(downleftneighbour);
            }
        } else {geldig.push_back(downleftneighbour);}
    }
    return geldig;
}

vector<pair<int, int>> Koningin::geldige_zetten(Game &g) {
    vector<pair<int, int>> geldig;
    for (int i = Koningin::getPosition().second - 1; i >= 0; --i) {
        if (g.getPiece(Koningin::getPosition().first, i) == nullptr) {
            pair<int, int> paar(Koningin::getPosition().first, i);
            geldig.push_back(paar);
        } else {
            if (Koningin::getKleur() != g.getPiece(Koningin::getPosition().first, i)->getKleur()) {
                pair<int, int> paar(Koningin::getPosition().first, i);
                geldig.push_back(paar);
            }
            break;}}

    for (int i = Koningin::getPosition().second + 1; i <= 7; ++i) {
        if (g.getPiece(Koningin::getPosition().first, i) == nullptr) {
            pair<int, int> paar(Koningin::getPosition().first, i);
            geldig.push_back(paar);
        } else {
            if (Koningin::getKleur() != g.getPiece(Koningin::getPosition().first, i)->getKleur()) {
                pair<int, int> paar(Koningin::getPosition().first, i);
                geldig.push_back(paar);
            }
            break;}}

    for (int i = Koningin::getPosition().first - 1; i >= 0; --i) {
        if (g.getPiece(i, Koningin::getPosition().second) == nullptr) {
            pair<int, int> paar(i, Koningin::getPosition().second);
            geldig.push_back(paar);
        } else {
            if (Koningin::getKleur() != g.getPiece(i, Koningin::getPosition().second)->getKleur()) {
                pair<int, int> paar(i, Koningin::getPosition().second);
                geldig.push_back(paar);
            }
            break;}}

    for (int i = Koningin::getPosition().first + 1; i <= 7; ++i) {
        if (g.getPiece(i, Koningin::getPosition().second) == nullptr) {
            pair<int, int> paar(i, Koningin::getPosition().second);
            geldig.push_back(paar);
        } else {
            if (Koningin::getKleur() != g.getPiece(i, Koningin::getPosition().second)->getKleur()) {
                pair<int, int> paar(i, Koningin::getPosition().second);
                geldig.push_back(paar);
            }
            break;}}

    for (int i = 1; i < 8-Koningin::getPosition().second; ++i) {
        if (g.getPiece(Koningin::getPosition().first + i, Koningin::getPosition().second + i) == nullptr) {
            pair<int, int> paar(Koningin::getPosition().first + i, Koningin::getPosition().second + i);
            geldig.push_back(paar);
        } else {
            if (Koningin::getPosition().first + i < 8 and Koningin::getPosition().second + i < 8) {
                if (Koningin::getKleur() != g.getPiece(Koningin::getPosition().first + i, Koningin::getPosition().second + i)->getKleur()) {
                    pair<int, int> paar(Koningin::getPosition().first + i, Koningin::getPosition().second + i);
                    geldig.push_back(paar);
                }
                break;}}}

    for (int i = 1; i < 8-Koningin::getPosition().second; ++i) {
        if (g.getPiece(Koningin::getPosition().first-i, Koningin::getPosition().second+i) == nullptr) {
            pair<int, int> paar (Koningin::getPosition().first-i, Koningin::getPosition().second+i);
            geldig.push_back(paar);
        } else {
            if (Koningin::getPosition().first-i >= 0 and Koningin::getPosition().second+i < 8) {
                if (Koningin::getKleur() != g.getPiece(Koningin::getPosition().first-i, Koningin::getPosition().second+i)->getKleur()) {
                    pair<int, int> paar (Koningin::getPosition().first-i, Koningin::getPosition().second+i);
                    geldig.push_back(paar);
                }
                break;}}}

    for (int i = 1; i <= Koningin::getPosition().second; ++i) {
        if (g.getPiece(Koningin::getPosition().first+i, Koningin::getPosition().second-i) == nullptr) {
            pair<int, int> paar (Koningin::getPosition().first+i, Koningin::getPosition().second-i);
            geldig.push_back(paar);
        } else {
            if (Koningin::getPosition().first+i < 8 and Koningin::getPosition().second-i >= 0) {
                if (Koningin::getKleur() != g.getPiece(Koningin::getPosition().first+i, Koningin::getPosition().second-i)->getKleur()) {
                    pair<int, int> paar (Koningin::getPosition().first+i, Koningin::getPosition().second-i);
                    geldig.push_back(paar);
                }
                break;}}}

    for (int i = 1; i <= Koningin::getPosition().second; ++i) {
        if (g.getPiece(Koningin::getPosition().first-i, Koningin::getPosition().second-i) == nullptr) {
            pair<int, int> paar (Koningin::getPosition().first-i, Koningin::getPosition().second-i);
            geldig.push_back(paar);
        } else {
            if (Koningin::getPosition().first-i >= 0 and Koningin::getPosition().second-i >= 0) {
                if (Koningin::getKleur() != g.getPiece(Koningin::getPosition().first-i, Koningin::getPosition().second-i)->getKleur()) {
                    pair<int, int> paar (Koningin::getPosition().first-i, Koningin::getPosition().second-i);
                    geldig.push_back(paar);
                }
                break;}}}
    int i = 0;
    while (i < geldig.size()) {
        if (geldig[i].first < 0 or geldig[i].first > 7 or geldig[i].second < 0 or geldig[i].second > 7 ) {
            geldig.erase(std::remove(geldig.begin(), geldig.end(), geldig[i]), geldig.end());
        } else {++i;}}
    return geldig;
}

vector<pair<int, int>> Loper::geldige_zetten(Game &g) {
    vector<pair<int, int>> geldig;
    for (int i = 1; i < 8-Loper::getPosition().second; ++i) {
        if (g.getPiece(Loper::getPosition().first + i, Loper::getPosition().second + i) == nullptr) {
            pair<int, int> paar(Loper::getPosition().first + i, Loper::getPosition().second + i);
            geldig.push_back(paar);
        } else {
            if (Loper::getPosition().first + i < 8 and Loper::getPosition().second + i < 8) {
                if (Loper::getKleur() != g.getPiece(Loper::getPosition().first + i, Loper::getPosition().second + i)->getKleur()) {
                    pair<int, int> paar(Loper::getPosition().first + i, Loper::getPosition().second + i);
                    geldig.push_back(paar);
                }
                break;}}}

    for (int i = 1; i < 8-Loper::getPosition().second; ++i) {
        if (g.getPiece(Loper::getPosition().first-i, Loper::getPosition().second+i) == nullptr) {
            pair<int, int> paar (Loper::getPosition().first-i, Loper::getPosition().second+i);
            geldig.push_back(paar);
        } else {
            if (Loper::getPosition().first-i >= 0 and Loper::getPosition().second+i < 8) {
                if (Loper::getKleur() != g.getPiece(Loper::getPosition().first-i, Loper::getPosition().second+i)->getKleur()) {
                    pair<int, int> paar (Loper::getPosition().first-i, Loper::getPosition().second+i);
                    geldig.push_back(paar);
                }
                break;}}}

    for (int i = 1; i <= Loper::getPosition().second; ++i) {
        if (g.getPiece(Loper::getPosition().first+i, Loper::getPosition().second-i) == nullptr) {
            pair<int, int> paar (Loper::getPosition().first+i, Loper::getPosition().second-i);
            geldig.push_back(paar);
        } else {
            if (Loper::getPosition().first+i < 8 and Loper::getPosition().second-i >= 0) {
                if (Loper::getKleur() != g.getPiece(Loper::getPosition().first+i, Loper::getPosition().second-i)->getKleur()) {
                    pair<int, int> paar (Loper::getPosition().first+i, Loper::getPosition().second-i);
                    geldig.push_back(paar);
                }
                break;}}}

    for (int i = 1; i <= Loper::getPosition().second; ++i) {
        if (g.getPiece(Loper::getPosition().first-i, Loper::getPosition().second-i) == nullptr) {
            pair<int, int> paar (Loper::getPosition().first-i, Loper::getPosition().second-i);
            geldig.push_back(paar);
        } else {
            if (Loper::getPosition().first-i >= 0 and Loper::getPosition().second-i >= 0) {
                if (Loper::getKleur() != g.getPiece(Loper::getPosition().first-i, Loper::getPosition().second-i)->getKleur()) {
                    pair<int, int> paar (Loper::getPosition().first-i, Loper::getPosition().second-i);
                    geldig.push_back(paar);
                }
                break;}}}
    int i = 0;
    while (i < geldig.size()) {
        if (geldig[i].first < 0 or geldig[i].first > 7 or geldig[i].second < 0 or geldig[i].second > 7 ) {
            geldig.erase(std::remove(geldig.begin(), geldig.end(), geldig[i]), geldig.end());
        } else {++i;}}
    return geldig;
}

vector<pair<int, int>> Paard::geldige_zetten(Game &g) {
    vector<pair<int, int>> geldig;
    pair<int, int> paardje = Paard::getPosition();

    if (paardje.first+2 < 8 and paardje.second+1 < 8) {
        if (g.getPiece(paardje.first+2, paardje.second+1) == nullptr) {
            pair<int, int> paar (paardje.first+2, paardje.second+1);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first+2,paardje.second+1)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar (paardje.first+2, paardje.second+1);
            geldig.push_back(paar);
    }}
    if (paardje.first+1 < 8 and paardje.second+2 < 8) {
        if (g.getPiece(paardje.first+1, paardje.second+2) == nullptr) {
            pair<int, int> paar (paardje.first+1, paardje.second+2);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first+1, paardje.second+2)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar (paardje.first+1, paardje.second+2);
            geldig.push_back(paar);
    }}
    if (paardje.first-2 >= 0 and paardje.second-1 >= 0) {
        if (g.getPiece(paardje.first-2, paardje.second-1) == nullptr) {
            pair<int, int> paar (paardje.first-2, paardje.second-1);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first-2, paardje.second-1)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar (paardje.first-2, paardje.second-1);
            geldig.push_back(paar);
        }}
    if (paardje.first-1 >= 0 and paardje.second-2 >= 0) {
        if (g.getPiece(paardje.first-1, paardje.second-2) == nullptr) {
            pair<int, int> paar (paardje.first-1, paardje.second-2);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first-1, paardje.second-2)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar (paardje.first-1, paardje.second-2);
            geldig.push_back(paar);
        }}
    if (paardje.first-2 >= 0 and paardje.second+1 < 8) {
        if (g.getPiece(paardje.first-2, paardje.second+1) == nullptr) {
            pair<int, int> paar (paardje.first-2, paardje.second+1);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first-2, paardje.second+1)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar (paardje.first-2, paardje.second+1);
            geldig.push_back(paar);
        }}
    if (paardje.first-1 >= 0 and paardje.second+2 < 8) {
        if (g.getPiece(paardje.first-1, paardje.second+2) == nullptr) {
            pair<int, int> paar (paardje.first-1, paardje.second+2);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first-1, paardje.second+2)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar (paardje.first-1, paardje.second+2);
            geldig.push_back(paar);
    }}
    if (paardje.first+2 < 8 and paardje.second-1 >= 0) {
        if (g.getPiece(paardje.first+2, paardje.second-1) == nullptr) {
            pair<int, int> paar (paardje.first+2, paardje.second-1);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first+2, paardje.second-1)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar (paardje.first+2, paardje.second-1);
            geldig.push_back(paar);
    }}
    if (paardje.first+1 < 8 and paardje.second-2 >= 0) {
        if (g.getPiece(paardje.first+1, paardje.second-2) == nullptr) {
            pair<int, int> paar (paardje.first+1, paardje.second-2);
            geldig.push_back(paar);
        }
        else if (g.getPiece(paardje.first+1, paardje.second-2)->getKleur() != Paard::getKleur()) {
            pair<int, int> paar(paardje.first + 1, paardje.second - 2);
            geldig.push_back(paar);
        }}
    return geldig;
}

vector<pair<int, int>> Toren::geldige_zetten(Game &g) {
    vector<pair<int, int>> geldig;
    for (int i = Toren::getPosition().second-1; i >= 0; --i) {
        if (g.getPiece(Toren::getPosition().first, i) == nullptr) {
            pair<int, int> paar (Toren::getPosition().first, i);
            geldig.push_back(paar);
        } else {
            if (Toren::getKleur() != g.getPiece(Toren::getPosition().first, i)->getKleur()) {
                pair<int, int> paar (Toren::getPosition().first, i);
                geldig.push_back(paar);
            }
            break;}}

    for (int i = Toren::getPosition().second+1; i <= 7; ++i) {
        if (g.getPiece(Toren::getPosition().first, i) == nullptr) {
            pair<int, int> paar (Toren::getPosition().first, i);
            geldig.push_back(paar);
        } else {
            if (Toren::getKleur() != g.getPiece(Toren::getPosition().first, i)->getKleur()) {
                pair<int, int> paar(Toren::getPosition().first, i);
                geldig.push_back(paar);
            }
            break;}}

    for (int i = Toren::getPosition().first-1; i >= 0; --i) {
        if (g.getPiece(i, Toren::getPosition().second) == nullptr) {
            pair<int, int> paar (i, Toren::getPosition().second);
            geldig.push_back(paar);
        } else {
            if (Toren::getKleur() != g.getPiece(i, Toren::getPosition().second)->getKleur()) {
                pair<int, int> paar(i, Toren::getPosition().second);
                geldig.push_back(paar);
            }
            break;}}

    for (int i = Toren::getPosition().first+1; i <= 7; ++i) {
        if (g.getPiece(i, Toren::getPosition().second) == nullptr) {
            pair<int, int> paar (i, Toren::getPosition().second);
            geldig.push_back(paar);
        } else {
            if (Toren::getKleur() != g.getPiece(i, Toren::getPosition().second)->getKleur()) {
                pair<int, int> paar(i, Toren::getPosition().second);
                geldig.push_back(paar);
            }
            break;}}
    return geldig;
}