#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <SvgDraggableItem.h>
#include <QHash>
#include <frameDrag.h>
#include <GraphicsViewDrop.h>
#include <QSplitter>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
    private:
        QGraphicsScene *scene;
        GraphicsViewDrop *view;
        QSplitter *sp;
        QHash<QString,QSvgRenderer *> rendererTable;
        frameDrag *frame;
    protected:
        void keyPressEvent(QKeyEvent * event);
};

#endif