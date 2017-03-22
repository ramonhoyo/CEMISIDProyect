#ifndef GRAPHICSVIEWDROP_H
#define GRAPHICSVIEWDROP_H
#include <QtSvg/QSvgRenderer>
#include <QGraphicsView>
#include <QHash>
#include <SvgDraggableItem.h>

/**
* @brief Class for reimplement methods for the class view
*/
 class GraphicsViewDrop : public QGraphicsView
 {
   public:
    GraphicsViewDrop(QWidget *parent = 0);
    GraphicsViewDrop(QGraphicsScene * scene, QWidget * parent = 0);
    void setRedererTable(QHash<QString,QSvgRenderer *> *render);
    void zoomIn();
    void zoomOut();
  private:
    QHash<QString,QSvgRenderer *> *rendererTable;
    QPoint init;
    int click;
    SvgDraggableItem  *first;
  protected:
    void dropEvent(QDropEvent * event) ;
    void dragEnterEvent(QDragEnterEvent *event) ;
    void dragMoveEvent(QDragMoveEvent *event) ;
    void mouseDoubleClickEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent *event);
  private:
    void scaleView(qreal scaleFactor);
};

#endif
