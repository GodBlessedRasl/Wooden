#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <AVL.h>
#include "ui_mainwindow.h"
#include "QGraphicsView"
#include "QDebug"
#include "Field.h"
#include "Dekart.h"
#include "vector"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    avl tree;
    int a = 63;
    int b = 40;
//    Field_vis* field;
//    std::vector<visual_node>vec;
    void avl_drawer(QGraphicsScene *scene, avl_node *cur, int x, int y);
public slots:
//    void gx_change();
private slots:
    void on_avl_button_clicked();

    void on_add_button_clicked();

    void on_rand_add_clicked();

    void on_DEL_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
