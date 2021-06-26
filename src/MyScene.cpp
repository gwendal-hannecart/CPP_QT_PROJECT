#include <fstream>
#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {
    std::srand(time(nullptr));
    this->setSceneRect(QRect(0,0,398,600));
    this->k-=0;
    this->pseudo=new QLineEdit();
    pseudo->grabKeyboard();
    pseudo->setMaxLength(8);
    pseudo->setInputMask("aaaaaaaa");
    pseudo->setPlaceholderText(QString("Entrez votre pseudo"));
    pseudo->setModified(true);
    pseudo->setCursorPosition(0);
    pseudo->setMinimumSize(350,20);
    pseudo->setReadOnly(false);
    pseudo->setEchoMode(QLineEdit::Normal);
    this->setBackgroundBrush(QColor((10,10,10)));
    this->addWidget(pseudo);
    explication=new QGraphicsTextItem("Appuyer sur la touche entrée pour valider");
    explication->setDefaultTextColor(QColor(255,119,0));
    explication->show();
    explication->setPos(0,pseudo->height());
    this->addItem(explication);
    timer = new QTimer(this);
    timer->start(30);
    connect(pseudo, SIGNAL(editingFinished()), this, SLOT(enregistrer()));
    connect(this, SIGNAL(perdu(QGraphicsPixmapItem *)), this, SLOT(rejouer(QGraphicsPixmapItem *)));
    connect(this, SIGNAL(limite(QGraphicsPixmapItem * )), this, SLOT(ChoixVoie(QGraphicsPixmapItem * )));
}

MyScene::~MyScene() {

}


void MyScene::enregistrer() {
    if(pseudo->hasAcceptableInput()) {
        pseudo->releaseKeyboard();
        pseudo->close();
        explication->hide();
        joueur = QString(pseudo->text());
        car = new QGraphicsPixmapItem();
        car->setPixmap(QPixmap("../resources/car-306222_640.png"));
        car->setPixmap(car->pixmap().scaled(QSize(150, 150), Qt::KeepAspectRatio, Qt::FastTransformation));
        car->setPos(60, 0-car->pixmap().width());
        car->setVisible(true);
        car->hide();
        this->addItem(car);
        car2 = new QGraphicsPixmapItem();
        car2->setVisible(false);
        car2->setPixmap(QPixmap("../resources/car-307714_640.png"));
        car2->setPixmap(car2->pixmap().scaled(QSize(150, 150), Qt::KeepAspectRatio, Qt::FastTransformation));
        car2->setPos(170, 0-car2->pixmap().width());
        car2->hide();
        this->addItem(car2);
        QGraphicsPixmapItem* haut= new QGraphicsPixmapItem();
        haut->setPixmap(QPixmap("../resources/haut_2.png"));
        haut->setPixmap(haut->pixmap().scaled(QSize(400,70)));
        haut->setPos(0,-haut->pixmap().height());
        this->addItem(haut);
        this->t = new QGraphicsPixmapItem();
        QGraphicsRectItem* rectangle=new QGraphicsRectItem();
        rectangle->setRect(40,0,5,650);
        rectangle->setBrush(Qt::yellow);
        rectangle->setPen(Qt::NoPen);
        this->addItem(rectangle);
        QGraphicsRectItem* rectangle2=new QGraphicsRectItem();
        rectangle2->setRect(355,0,5,650);
        rectangle2->setBrush(Qt::yellow);
        rectangle2->setPen(Qt::NoPen);
        this->addItem(rectangle2);
        for(int i=0;i<2;i++){
            for(int j=0;j<7;j++){
                QGraphicsRectItem* rectangle3=new QGraphicsRectItem();
                rectangle3->setBrush(Qt::yellow);
                rectangle3->setPen(Qt::NoPen);
                rectangle3->setRect(150+i*100,10+(40+60)*j,5,60);
                this->addItem(rectangle3);
            }
        }
        this->setBackgroundBrush(QColor((10,10,10)));
        //this->addItem(rectangle2);
        perso = new QGraphicsPixmapItem();
        perso->setPixmap(QPixmap("../resources/turtle.png"));
        perso->setPixmap(perso->pixmap().scaled(QSize(80, 80)));
        perso->setPos(200,530);
        this->addItem(perso);
        perso->hide();
        score = 0;
        sce = new QGraphicsTextItem();
        sce->setDefaultTextColor(QColor(255,119,0));
        //setBackgroundBrush(QColor((10,10,10)));
        sce->setPlainText(QString("Score : %1").arg(score));
        sce->setPos(0, -40);
        this->addItem(sce);
        qgti = new QGraphicsTextItem(QString("Meilleur Joueur: %1 Score:%2").arg(getPseudoMeilleurJoueur()).arg(getMeilleurScore()));
        qgti->setDefaultTextColor(QColor(255,119,0));
        this->addItem(qgti);
        qgti->hide();
        qgti->setPos(180, -40);
        pause=new QGraphicsTextItem("PAUSE");
        this->addItem(pause);
        pause->hide();//On le cache au début
        level = new QGraphicsTextItem(QString("Niveau %1").arg(score / 10));
        level->setDefaultTextColor(QColor(249, 92, 1));
        level->font().setStretch(100);
        level->setScale(5);
        level->font().setStyleStrategy(QFont::PreferDevice);
        level->hide();
        this->addItem(level);
        car->setPos(60, 1 - this->car->boundingRect().height());
        timer->stop();
        timer->start(30);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    }
}

void MyScene::rejouer(QGraphicsPixmapItem * Qg) {
    timer->stop();
    this->k=0;
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QMessageBox msgBox;
    msgBox.activateWindow();
    msgBox.setText("Game over");
    is_moving_right=false;
    is_moving_left=false;
    msgBox.setModal(true);
    QPushButton p("rejouer");
    msgBox.addButton("rejouer", QMessageBox::RejectRole);
    msgBox.addButton("exit", QMessageBox::RejectRole);
    QString str = "Pseudo";
    perso->setPos(230,530);
    QFile* file=new QFile("../resources/winner.txt");
    file->open(QIODevice::ReadWrite);
    QTextStream lecture(file);
    QString meilleurjoueur=QString();
    meilleurjoueur=meilleurjoueur+lecture.readLine();
    if(meilleurjoueur.size()!=0){
        int i=1;
        while(std::isdigit(meilleurjoueur.toStdString()[i])==false && meilleurjoueur.toStdString()[i-1]!=' '){
            i++;
        }
        QStringList list1;
        list1.append(meilleurjoueur.left(i));
        list1.append(meilleurjoueur.right(meilleurjoueur.size()-i));
        int scoreMeilleurJoueur=std::stoi(list1[1].toStdString());
        if(this->score>scoreMeilleurJoueur){
            file->remove();
            file->open(QIODevice::ReadWrite);
            QString chaine=QString("%1 %2").arg(pseudo->text()).arg(this->score);
            file->write( chaine.toStdString().c_str());
            file->close();
        }
    }else{
        QString chaine=QString("%1 %2").arg(pseudo->text()).arg(this->score);
        std::string chaine2= chaine.toStdString();
        file->write( chaine2.c_str());
        file->close();
    }
    msgBox.exec();
    if(msgBox.clickedButton()->text()=="rejouer"){
        score=0;
        sce->hide();
        sce->setPlainText(QString("Score : %1").arg(score));
        Qg->setPos(170,1);
        Qg->setVisible(true);
        qgti->setPlainText(QString("Meilleur Joueur: %1 Score:%2").arg(getPseudoMeilleurJoueur()).arg(getMeilleurScore()));
        msgBox.close();
        timer->start(30);
        this->setActivePanel(perso);
    }
    if(msgBox.clickedButton()->text()=="exit"){
        msgBox.close();
        exit(0);
    }

}

void MyScene::update(){
    QPointF p1(60,0-car->pixmap().width());
    QPointF p2(170,0-car->pixmap().width());
    QPointF p3(280,0-car->pixmap().width());
if(((car->pos().x()>=p1.x() && car->pos().y()>=p1.y()) || (car->pos().x()>=p2.x() && car->pos().y()>=p2.y()) || (car->pos().x()>=p3.x() && car->pos().y()>=p3.y())) && car2->isVisible()==false ) {
    car->show();
}
if( ((car2->pos().x()>=p1.x() && car2->pos().y()>=p1.y()) || (car2->pos().x()>=p2.x() && car2->pos().y()>=p2.y()) || (car2->pos().x()>=p3.x() && car2->pos().y()>=p3.y())) &&  car->isVisible()==false){
    car2->show();
}
    perso->show();
    this->qgti->show();
    QKeyEvent *event = new QKeyEvent(QEvent::GrabKeyboard, 188, Qt::MetaModifier, QString());
    sce->hide();
    this->sce->setPlainText(QString("Score : %1").arg(score));
    sce->show();
     if(perso->collidesWithItem(car) || perso->collidesWithItem(car2)  ){
       if(perso->collidesWithItem(car)) {
           timer->stop();
           event->ignore();
           perso->setPos(250,530);
           car->setVisible(false);
           car->setPos(170,1);
           car2->setPos(170,1);
           sce->hide();
           qgti->hide();
           emit perdu(car);
       }
         if(perso->collidesWithItem(car2)) {
             timer->stop();
             event->ignore();
             perso->setPos(250,530);
             car2->setVisible(false);
             car->setPos(170,1);
             car2->setPos(170,1);
             sce->hide();
             qgti->hide();
             emit perdu(car2);
         }

     }
    else {
            keyBoardEvent(event);
            if(car->isVisible()) {
                 QPointF pos = car->pos();
                 car->setPos(pos.rx(), pos.ry() + 4 + (k / 10));
                 this->limitebot();
            }
            if(car2->isVisible()){
                 QPointF pos = car2->pos();
                 car2->setPos(pos.rx(), pos.ry() + 4 + (k / 10));
                 this->limitebot();
            }
    }
}

void MyScene::keyBoardEvent(QKeyEvent *event) {
    if(timer->isActive()==true) {
        if (is_moving_left==true && perso->pos().x()>this->sceneRect().left()) {
            QPointF pos = perso->pos();
            perso->setPos(pos.rx() - 10 , pos.ry());
        }
        if (is_moving_right==true && perso->pos().x()<this->sceneRect().right()-perso->boundingRect().width()) {
            QPointF pos = perso->pos();
            perso->setPos(pos.rx() + 10 , pos.ry());
        }
    }
}

void MyScene::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Left) {
        is_moving_left = true;
        return;
    }
    if (event->key() == Qt::Key_Right) {
        is_moving_right = true;
        return;
    }

}

void MyScene::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_P) {
        pause->setDefaultTextColor(QColor(249, 92, 1));
        pause->font().setStretch(200);
        pause->setScale(10);
        pause->font().setStyleStrategy(QFont::PreferDevice);
        if (timer->isActive() == true) {
            timer->stop();
            pause->setPos(-50, 200);
            pause->show();
            is_moving_left = false;
            is_moving_right = false;
        } else {
            pause->hide();
            timer->start();
        }
    }
    if (event->key() == Qt::Key_Left) {
        is_moving_left = false;
        return;
    }
    if (event->key() == Qt::Key_Right) {
        is_moving_right = false;
        return;
    }
    if (event->key() == Qt::Key_End) {
        this->clear();
        exit(0);
    }
}

void MyScene::limitebot( ){
   if( car->pos().y()>=this->height()+this->car->boundingRect().height() ) {
       this->car->setVisible(false);
       this->car2->setVisible(true);
       this->car->setPos(170,-car->pixmap().height());
       emit limite(car);
       return;
   }
   if( car2->pos().y()>=this->height()+this->car2->boundingRect().height() ) {
        this->car2->setVisible(false);
        this->car->setVisible(true);
        this->car2->setPos(170,-car2->pixmap().height());
        emit limite(car2);
        return;
        }
}

void MyScene::ChoixVoie(QGraphicsPixmapItem* Qg) {
    k = k + 1;
    if (score < 10) {
        score = score + 1;
    } else {
        score = score + k / 10;
    }

    if (k % 10 == 0) {
        this->level->setPlainText(QString("Niveau %1").arg(k / 10));
        level->show();
    }else {
        level->hide();
    }
        int choixroute = rand() % 3;
        if (choixroute == 0) {
            Qg->setPos(60,  -Qg->pixmap().height());
            return;
        }
        if (choixroute == 1) {
            Qg->setPos(170,  -Qg->pixmap().height());

            return;
        }
        if (choixroute == 2) {
            Qg->setPos(280, -Qg->pixmap().height());

            return;
        }
    }


void MyScene::change() {
    t->setPixmap(t->pixmap().scaled(QSize(this->width(),this->height()),Qt::KeepAspectRatio, Qt::FastTransformation));
}

int MyScene::getMeilleurScore() {
    QFile* file=new QFile("../resources/winner.txt");
    file->open(QIODevice::ReadOnly);
    QTextStream lecture(file);
    QString meilleurjoueur=QString();
    meilleurjoueur=meilleurjoueur+lecture.readLine();
    int i=1;
    while(std::isdigit(meilleurjoueur.toStdString()[i])==false || meilleurjoueur.toStdString()[i-1]!=' '){
        i++;
    }
    QStringList list1;
    list1.append(meilleurjoueur.right(meilleurjoueur.size()-i));
    int scoreMeilleurJoueur=std::stoi(list1[0].toStdString());
    return scoreMeilleurJoueur;
}

QString MyScene::getPseudoMeilleurJoueur() {
    QFile* file=new QFile("../resources/winner.txt");
    file->open(QIODevice::ReadOnly);
    QTextStream lecture(file);
    QString meilleurjoueur=QString();
    meilleurjoueur=meilleurjoueur+lecture.readLine();
    int i=1;
    while(std::isdigit(meilleurjoueur.toStdString()[i])==false || meilleurjoueur.toStdString()[i-1]!=' '){
        i++;
    }
    QStringList list1;
    list1.append(meilleurjoueur.left(i));
    return list1[0];
}

void MyScene::exitFunct() {
    this->clear();
    exit(0);
}

