#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsView"
#include "QGraphicsTextItem"
#include "AVL.h"
#include "QDebug"
#include "algorithm"
#include "math.h"
#include "bits/stdc++.h"
#include "Field.h"
#include "Dekart.h"
#include "QProgressBar"

//int gx, gy;
//QProgressBar* bar = new QProgressBar;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    bar->setRange(-200000000, 200000000);
//    connect(bar, SIGNAL(valueChanged(int)), this, SLOT(gx_change()));


//    QPalette pal = ui->avl_button->palette();
//    pal.setColor(QPalette::Button, QColor(Qt::blue));
//    ui->avl_button->setAutoFillBackground(true);
//    ui->avl_button->setPalette(pal);
//    ui->avl_button->update();


//    field = new Field_vis;
    ui->centralwidget->setStyleSheet("background-color:pink;");
//    avl tree;
//    tree.push(5);
//    tree.push(4);
//    tree.pop(5);
//    qDebug() << tree.get()->element;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: avl_drawer(QGraphicsScene *avl_scene, avl_node *cur, int x, int y){
    if(cur==nullptr){
        return;
    }else{
        QPen *pen = new QPen;
        pen->setColor(Qt::red);
        avl_scene->addEllipse(x,y,a,b,*pen);
//        std::string now = "";
//        int k = cur->element;
//        while(k){
//            now+=char(k%10 - '0');
//            k/=10;
//        }
//        std::reverse(now.begin(),now.end());
//        vec.push_back(visual_node(x,y,cur->element));
        QGraphicsTextItem *num = new QGraphicsTextItem(QString::number(cur->element));
        num->setPos(x, y+10);
        avl_scene->addItem(num);
        ui->field->setScene(avl_scene);
        if(cur->high == 2){
            if(cur->left != nullptr){
                avl_scene->addLine(x+a/2, y+b, x - 2*a/3 + a/2, y + 3*b/2);
            }
            avl_drawer(avl_scene, cur->left, x - 2*a/3, y + 3*b/2);
            if(cur->right != nullptr){
                avl_scene->addLine(x+a/2, y+b, x + 2*a/3 + a/2, y + 3*b/2);
            }
            avl_drawer(avl_scene, cur->right, x + 2*a/3, y + 3*b/2);
        }else if(cur->high !=1){
            int k = std::pow(2,cur->high - 3);
            if(cur->left!=nullptr){
                avl_scene->addLine(x+a/2,y+b,x - 4*a*k/3 + a/2, y + 3*b/2);
            }
            avl_drawer(avl_scene, cur->left, x - 4*a*k/3, y + 3*b/2);
            if(cur->right!=nullptr){
                avl_scene->addLine(x+a/2,y+b,x + 4*a*k/3 + a/2, y + 3*b/2);
            }
            avl_drawer(avl_scene, cur->right, x + 4*a*k/3, y +3*b/2);
        }
    }
}

void MainWindow::on_avl_button_clicked() {
//    ui->MainLay->addWidget(field);
    QGraphicsScene *avl_scene = new QGraphicsScene;
    avl_drawer(avl_scene, tree.get(), 0, 0);
//    QPen *pen = new QPen;
//    pen->setColor(Qt::red);
//    scene->addEllipse(0,0,500,100,*pen);
//    scene->addEllipse(0,0,50,10,*pen);
//    ui->field->setScene(scene);
}

void MainWindow::on_add_button_clicked()
{
    std::string s = ui->Number->text().toStdString();
    int num = std::atoi(s.c_str());
    if(num<100000000){
        tree.push(num);
//        for(int i = 0;i<vec.size();++i){
//            qDebug() << vec[i].elem<<" ";
//        }
//        qDebug() << "\n";
//        vec.clear();
        QGraphicsScene *avl_scene = new QGraphicsScene;
        avl_drawer(avl_scene, tree.get(), 0, 0);
    }
}

void MainWindow::on_rand_add_clicked()
{
    std::string s1 = ui->minn->text().toStdString();
    std::string s2 = ui->maxx->text().toStdString();
    std::string s3 = ui->Kolvo->text().toStdString();
    int beg = std::atoi(s1.c_str());
    int kon = std::atoi(s2.c_str());
    int kolvo = std::atoi(s3.c_str());
    if(kolvo<=1000){
        srand ( time(NULL) );
        for(size_t i = 0; i < kolvo; ++i){
            int now = rand() % (kon - beg + 1) + beg;
            if(now<100000000){
                tree.push(now);
            }
        }
        QGraphicsScene *avl_scene = new QGraphicsScene;
        avl_drawer(avl_scene, tree.get(), 0, 0);
    }
}

//void Field_vis:: mousePressEvent(QMouseEvent *event){
//    QPointF point = mapToScene(event->pos());
////    qDebug() << point.x() << " "<< point.y();
//    gx = point.x();
//    gy = point.y();
//    bar->setValue(gx);
//}

//void MainWindow::gx_change(){

//}

void MainWindow::on_DEL_clicked()
{
    std::string s = ui->del_num->text().toStdString();
    int num = std::atoi(s.c_str());
    if(num<100000000){
        tree.pop(num);
        QGraphicsScene *avl_scene = new QGraphicsScene;
        avl_drawer(avl_scene, tree.get(), 0, 0);
    }
}
