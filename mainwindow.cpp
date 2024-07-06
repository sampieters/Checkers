#include "mainwindow.h"
#include "SchaakStuk.h"
#include <QMessageBox>
#include <QtWidgets>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new ChessBoard;
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);

    connect(scene,SIGNAL(clicked(int,int)),this,SLOT(clicked(int,int)));

    createActions();
    createMenus();
    newGame();
}

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void MainWindow::clicked(int r, int k) {
    // Dit is de eerste klik
    if (firstclick == nullptr) {
        if (g.getPiece(r, k) == nullptr) {
            cout << "Kies eerst een schaakstuk" << endl;
        } else if (g.getPiece(r, k)->getKleur() == currentplayer) {
            scene->removeAllMarking();
            for (int i = 0; i < g.getPiece(r, k)->geldige_zetten(g).size(); i++) {
                scene->setTileFocus(g.getPiece(r, k)->geldige_zetten(g)[i].first,
                                    g.getPiece(r, k)->geldige_zetten(g)[i].second, display_moves->isChecked());
            }
            vector<pair<int, int>> danger;
            for (int i = 0; i <= 7; ++i) {
                for (int j = 0; j <= 7; ++j) {
                    if (g.getPiece(i, j) != nullptr) {
                        if (g.getPiece(i,j)->getKleur() != g.getPiece(r, k)->getKleur()) {
                            if (g.getPiece(i,j)->piece().type() != Piece::Pawn) {
                                for (int k = 0; k < g.getPiece(i,j)->geldige_zetten(g).size(); ++k) {
                                    danger.push_back(g.getPiece(i,j)->geldige_zetten(g)[k]);
                            }} else {
                                if (g.getPiece(i,j)->getKleur() == wit) {
                                    pair<int, int> links (g.getPiece(i,j)->getPosition().first-1, g.getPiece(i,j)->getPosition().second-1);
                                    pair<int, int> rechts (g.getPiece(i,j)->getPosition().first-1, g.getPiece(i,j)->getPosition().second+1);
                                    danger.push_back(links);
                                    danger.push_back(rechts);
                                } else {
                                    pair<int, int> links (g.getPiece(i,j)->getPosition().first+1, g.getPiece(i,j)->getPosition().second-1);
                                    pair<int, int> rechts (g.getPiece(i,j)->getPosition().first+1, g.getPiece(i,j)->getPosition().second+1);
                                    danger.push_back(links);
                                    danger.push_back(rechts);
                                }}}}}}
            firstclick = g.getPiece(r, k);
            for (auto & k : danger) {
                for (int i = 0; i < firstclick->geldige_zetten(g).size(); ++i) {
                    if (k == firstclick->geldige_zetten(g)[i]) {
                        scene->setTileThreat(k.first, k.second, true);
                    }}}

            scene->setTileSelect(r, k, true);
        } else { cout << "Het is niet uw beurt" << endl; }}

        // De tweede klik, maar de tweede klik in een vriendelijk stuk
    else if (g.getPiece(r, k) != nullptr and g.getPiece(r, k)->getKleur() == currentplayer) {
        for (int i = 0; i < firstclick->geldige_zetten(g).size(); i++) {
            scene->setTileFocus(firstclick->geldige_zetten(g)[i].first, firstclick->geldige_zetten(g)[i].second,
                                false);
        }
        scene->setTileSelect(firstclick->getPosition().first, firstclick->getPosition().second, false);
        vector<pair<int, int>> danger;
        for (int i = 0; i <= 7; ++i) {
            for (int j = 0; j <= 7; ++j) {
                if (g.getPiece(i, j) != nullptr) {
                    if (g.getPiece(i,j)->getKleur() != g.getPiece(r, k)->getKleur()) {
                        if (g.getPiece(i,j)->piece().type() != Piece::Pawn) {
                            for (int k = 0; k < g.getPiece(i,j)->geldige_zetten(g).size(); ++k) {
                                danger.push_back(g.getPiece(i,j)->geldige_zetten(g)[k]);
                            }} else {
                            if (g.getPiece(i,j)->getKleur() == wit) {
                                pair<int, int> links (g.getPiece(i,j)->getPosition().first-1, g.getPiece(i,j)->getPosition().second-1);
                                pair<int, int> rechts (g.getPiece(i,j)->getPosition().first-1, g.getPiece(i,j)->getPosition().second+1);
                                danger.push_back(links);
                                danger.push_back(rechts);
                            } else {
                                pair<int, int> links (g.getPiece(i,j)->getPosition().first+1, g.getPiece(i,j)->getPosition().second-1);
                                pair<int, int> rechts (g.getPiece(i,j)->getPosition().first+1, g.getPiece(i,j)->getPosition().second+1);
                                danger.push_back(links);
                                danger.push_back(rechts);
                            }}}}}}
        firstclick = g.getPiece(r, k);
        for (auto & k : danger) {
            for (int i = 0; i < firstclick->geldige_zetten(g).size(); ++i) {
                if (k == firstclick->geldige_zetten(g)[i]) {
                    scene->setTileThreat(k.first, k.second, true);
                }}}
        scene->setTileSelect(r, k, true);
        for (int i = 0; i < g.getPiece(r, k)->geldige_zetten(g).size(); i++) {
            scene->setTileFocus(g.getPiece(r, k)->geldige_zetten(g)[i].first,
                                g.getPiece(r, k)->geldige_zetten(g)[i].second, display_moves->isChecked());
        }}

    else {
        for (int i = 0; i < firstclick->geldige_zetten(g).size(); i++) {
            scene->setTileFocus(firstclick->geldige_zetten(g)[i].first, firstclick->geldige_zetten(g)[i].second,
                                false);
        }
        scene->removeAllMarking();
        vorige.push_back(g);
        if (g.move(firstclick, r, k)) {
            if (g.schaak(firstclick->getKleur())) {
                undo();
                volgende.pop_back();
        }
            this->update();

            if (currentplayer == wit) {
                if (g.schaak(zwart)) {
                    //if (g.schaakmat(zwart)) {
                    //    QMessageBox schaakmat;
                    //    schaakmat.setText(QString("Zwart staat schaakmat"));
                    //    schaakmat.exec();
                    //}
                //else {
                        QMessageBox schaak;
                        schaak.setText(QString("Zwart staat schaak"));
                        schaak.exec();
                  //  }
            }
                currentplayer = zwart;
            } else {
                if (g.schaak(wit)) {
                    //if (g.schaakmat(wit)) {
                    //    QMessageBox schaakmat;
                    //    schaakmat.setText(QString("Wit staat schaakmat"));
                    //    schaakmat.exec();
                    //} else {
                        QMessageBox schaak;
                        schaak.setText(QString("Wit staat schaak"));
                        schaak.exec();
                    //}
            }
                currentplayer = wit;}
            firstclick = nullptr;
    }}}

void MainWindow::newGame() {
    vorige.clear();
    volgende.clear();
    g.setStartBord();
    currentplayer = wit;
    scene->removeAllMarking();
    this->update();
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save game"), "",
                                                    tr("Chess File (*.chs);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream out(&file);
        /////////////////////////////////////////
        for  (int i=0; i<8;i++) {
            for (int j=0; j<8;j++) {
                if (g.getPiece(i, j) != nullptr) {
                    if (g.getPiece(i, j)->getKleur() == zwart) {
                        if (g.getPiece(i, j)->piece().type() == Piece::Rook) {
                            out << QString("Rb");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Bishop)) {
                            out << QString("Bb");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Knight)) {
                            out << QString("Hb");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::King)) {
                            out << QString("Kb");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Queen)) {
                            out << QString("Qb");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Pawn)) {
                            out << QString("Bb");
                        }}

                    else {
                        if (g.getPiece(i, j)->piece().type() == Piece::Rook) {
                            out << QString("Rw");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Bishop)) {
                            out << QString("Bw");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Knight)) {
                            out << QString("Hw");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::King)) {
                            out << QString("Kw");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Queen)) {
                            out << QString("Qw");
                        }
                        else if ((g.getPiece(i, j)->piece().type() == Piece::Pawn)) {
                            out << QString("Bw");
                        }
                    }
                }
                else {out << QString(".");}
            }

        }
    }
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load game"), "",
                                                    tr("Chess File (*.chs);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Error reading file "+fileName);
                    }
                }
                debugstring += "\n";
            }
            QMessageBox::information(this, tr("Debug"),
                                     debugstring);
        } catch (QString& Q) {
            QMessageBox::information(this, tr("Error reading file"),
                                     Q);
        }

    }
    update();
}

void MainWindow::undo() {
    if (!vorige.empty()) {
        volgende.push_back(g);
        Game current = vorige[vorige.size()-1];
        vorige.pop_back();
        g = current;
        for (int i = 0; i <= 7; ++i) {
            for (int j = 0; j <= 7; ++j) {
                if (g.getPiece(i, j) != nullptr) {
                    pair<int, int> terug(i, j);
                    g.getPiece(i, j)->setPosition(terug);
                }}}
        if (currentplayer == wit) {
            currentplayer = zwart;
        } else { currentplayer = wit; }
        firstclick = nullptr;
        this->update();}
    else {
        QMessageBox box;
        box.setText(QString("undo gaat niet"));
        box.exec();
    }
}

void MainWindow::redo() {
    if (!volgende.empty()) {
        Game current = volgende[volgende.size()-1];
        vorige.push_back(g);
        volgende.pop_back();
        g = current;
        for (int i = 0; i <= 7; ++i) {
            for (int j = 0; j <= 7; ++j) {
                if (g.getPiece(i, j) != nullptr) {
                    pair<int, int> next(i, j);
                    g.getPiece(i, j)->setPosition(next);
                }}}
        if (currentplayer == wit) {
            currentplayer = zwart;
        } else { currentplayer = wit; }
        firstclick = nullptr;
        this->update();
    } else {
        QMessageBox box;
        box.setText(QString("redo gaat niet"));
        box.exec();
    }
}

void MainWindow::visualizationChange() {
    QMessageBox box;
    QString visstring = QString(display_moves->isChecked()?"T":"F")+(display_kills->isChecked()?"T":"F")+(display_threats->isChecked()?"T":"F");
    box.setText(QString("Visualization changed : ")+visstring);
    box.exec();
}

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void MainWindow::update() {
    scene->clearBoard();
    for (int x = 0; x < 8 ; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (g.getPiece(x, y) == nullptr) {
                scene->setItem(x, y, Piece());
        } else {scene->setItem(x, y, g.getPiece(x, y)->piece());}}}

    if (display_kills->isChecked()) {
        for (int i = 0; i <= 7; ++i) {
            for (int j = 0; j <= 7; ++j) {
                if (g.getPiece(i, j) != nullptr and g.getPiece(i, j)->getKleur() != currentplayer) {
                    for (int k = 0; k < g.getPiece(i, j)->geldige_zetten(g).size(); ++k) {
                        if (g.getPiece(g.getPiece(i, j)->geldige_zetten(g)[k].first,g.getPiece(i, j)->geldige_zetten(g)[k].second)) {
                        scene->setPieceThreat(g.getPiece(i, j)->geldige_zetten(g)[k].first,
                                              g.getPiece(i, j)->geldige_zetten(g)[k].second, true);
                    }}}}}}
    if (display_threats->isChecked()) {
        for (int i = 0; i <= 7; ++i) {
            for (int j = 0; j <= 7; ++j) {
                if (g.getPiece(i, j) != nullptr and g.getPiece(i, j)->getKleur() == currentplayer) {
                    for (int k = 0; k < g.getPiece(i, j)->geldige_zetten(g).size(); ++k) {
                        if (g.getPiece(g.getPiece(i, j)->geldige_zetten(g)[k].first,g.getPiece(i, j)->geldige_zetten(g)[k].second)) {
                            scene->setPieceThreat(g.getPiece(i, j)->geldige_zetten(g)[k].first,
                                                  g.getPiece(i, j)->geldige_zetten(g)[k].second, true);
                        }}}}}}
}

void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Start a new game"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newGame);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read game from disk"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save game to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last move"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last undone move"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    display_moves= new QAction(tr("&valid moves"), this);
    display_moves->setStatusTip(tr("Show valid moves"));
    display_moves->setCheckable(true);
    display_moves->setChecked(true);
    connect(display_moves, &QAction::triggered, this, &MainWindow::visualizationChange);

    display_kills= new QAction(tr("threathed &enemy"), this);
    display_kills->setStatusTip(tr("Highlight threathened pieces (enemy)"));
    display_kills->setCheckable(true);
    display_kills->setChecked(true);
    connect(display_kills, &QAction::triggered, this, &MainWindow::visualizationChange);

    display_threats= new QAction(tr("threathed &player"), this);
    display_threats->setStatusTip(tr("Highlight threathened pieces (player)"));
    display_threats->setCheckable(true);
    display_threats->setChecked(true);
    connect(display_threats, &QAction::triggered, this, &MainWindow::visualizationChange);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(undoAct);
    gameMenu->addAction(redoAct);

    visualizeMenu = menuBar()->addMenu(tr("&Visualize"));
    visualizeMenu->addAction(display_moves);
    visualizeMenu->addAction(display_kills);
    visualizeMenu->addAction(display_threats);
}

void MainWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Spel verlaten"),
                                                  tr("Bent u zeker dat u het spel wil verlaten?\nNiet opgeslagen wijzigingen gaan verloren.")))
    {QApplication::quit();}
}

