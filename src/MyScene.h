#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTime>
#include <cmath>
#include <iostream>
#include <QObject>
#include <QDebug>
#include<QFormLayout>
#include <QKeyEvent>
#include <QEvent>
#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QIODevice>
#include <QFileDevice>
#include<QStringList>
#include<QtGlobal>
#include<QFile>
#include <QPushButton>
#include <string>
#include <cstring>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QSizePolicy>
#include <QMessageBox>
#include<QLabel>
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>
#include<QDialog>
#include <QLineEdit>
#include <QInputDialog>
#include <QAction>
#include<ctime>

class MyScene : public QGraphicsScene {
    Q_OBJECT
private:
    void keyBoardEvent(QKeyEvent* event);
    void keyReleaseEvent (QKeyEvent* event);
    void keyPressEvent (QKeyEvent* event);
protected:
    int  score;
    QString joueur;
    QLineEdit* pseudo;
    QGraphicsTextItem* sce;
    QGraphicsTextItem* pause;
    QTimer* timer;
    QTimer* timer2;
    int k=0;
    QGraphicsPixmapItem* perso;
    QGraphicsTextItem* qgti;
    QGraphicsPixmapItem* t;
    QGraphicsPixmapItem* car;
    QGraphicsTextItem *level;
    QGraphicsPixmapItem* car2;
    QGraphicsTextItem* explication;
    bool is_moving_left=false;
    bool is_moving_right=false;

public slots:
            void update();
            void ChoixVoie(QGraphicsPixmapItem* Qg);
            void limitebot();
            void change();
            void rejouer(QGraphicsPixmapItem * Qg);
            void enregistrer();
            void exitFunct();

signals:
    void limite( QGraphicsPixmapItem* Qg);
    void perdu(QGraphicsPixmapItem * Qg);

public:
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();
    int getMeilleurScore();
    QString getPseudoMeilleurJoueur();

};

#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
