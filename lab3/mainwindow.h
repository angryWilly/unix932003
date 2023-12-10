#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QSpacerItem>
#include <cmath>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QPushButton *mirrorButton;
    QPushButton *graphButton;
    QTextEdit *outputTextEdit;
    QTextEdit *textEdit;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QVBoxLayout *vBoxLayout;

private slots:
    void handleMirrorButtonClick();
    void handleGraphButtonClick();
};

#endif
