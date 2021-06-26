#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    Ql=new QLabel("Bienvenue",this);
    this->setWindowTitle("Menu principal");
    this->resize(400, 700);
    this->setFixedSize(400,700);
    this->setPalette(QPalette(QColor(20,20,20)));
    /*fond = new QGraphicsPixmapItem();
    fond->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    fond->setPixmap(QPixmap("../resources/RaceCircuitInterlagos2.png"));
    fond->setPixmap(fond->pixmap().scaled(QSize(400, 800)));
    fond->setPos(200,200);
    fond->show();*/
    timer = new QTimer();
    button=new QPushButton("jouer",this);
    button->setGeometry(100,200,50,50);
    button->show();//on le montre
    QPushButton* button2=new QPushButton("exit",this);
    button2->setParent(this);
    button2->setGeometry(200,200,50,50);
    button2->show();
    helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *actionHelp = new QAction(tr("&About"), this);
    helpMenu->addAction(actionHelp);
    QMenu* Commande= helpMenu->addMenu("&Commande");
    Commande->addAction(tr("P : Pause\n"));
    Commande->addAction(tr("Flèche de droite: se déplacer à droite\n"));
    Commande->addAction(tr("Flèche de Gauche: se déplacer à gauche\n"));
    QMenu* Principe= helpMenu->addMenu("&Principe");
    Principe->addAction(tr("Le jeu consiste à esquiver des voitures\n"));
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    connect(button, SIGNAL(pressed()), this, SLOT(start()));
    connect(button2, SIGNAL(pressed()), this, SLOT(exit()));
    timer->start();


}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet réalisé par Gwendal CIR2 Nantes");
    msgBox.setModal(true);
    msgBox.exec();

}

void MainWindow::start() {
    button->setDisabled(true);
    mainScene = new MyScene;
    mainView = new QGraphicsView;
    //mainView->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    mainView->setScene(mainScene);
    this->setCentralWidget(mainView);

}

void MainWindow::exit() {
   this->close();
}
