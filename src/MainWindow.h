#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include<QToolBar>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include<QLabel>
#include <QMessageBox>
#include<QInputDialog>
#include<QPushButton>
#include "MyScene.h"
#include <QGraphicsRectItem>
#include<QGraphicsPixmapItem>
#include<QMessageBox>

class MainWindow : public QMainWindow {
    Q_OBJECT
private :
    QLabel* Ql;
    QGraphicsPixmapItem* fond;
    QPushButton* button;
    MyScene* mainScene;
    QGraphicsView* mainView;
    QMenu* helpMenu;
    QTimer* timer;

signals:
    void limite();

public slots:
    void start();
    void exit();
    void slot_aboutMenu();

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();


};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
