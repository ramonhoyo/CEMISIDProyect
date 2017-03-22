#ifndef MGRAPHICSSCENE
#define MGRAPHICSSCENE
#include <QtGui>
#include <QGraphicsScene>

class MGraphicsScene : public QGraphicsScene
{
  public:
    MGraphicsScene(QObject *parent = 0);
  protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

#endif
