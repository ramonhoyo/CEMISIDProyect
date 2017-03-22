#ifndef GRAPHICSVIEWDROP_H
#define GRAPHICSVIEWDROP_H
#include <QSvgRenderer>
#include <QGraphicsView>
#include <QHash>
class GraphicsViewDrop : public QGraphicsView
{
    public:
        GraphicsViewDrop(QWidget *parent = 0);
        GraphicsViewDrop(QGraphicsScene * scene, QWidget * parent = 0);
        void setRedererTable(QHash<QString,QSvgRenderer *> *render);
    private:
        QHash<QString,QSvgRenderer *> *rendererTable;
    protected:
        void dropEvent(QDropEvent * event);
        void dragEnterEvent(QDragEnterEvent *event);
        void dragMoveEvent(QDragMoveEvent *event);
};

#endif
