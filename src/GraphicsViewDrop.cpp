#include "GraphicsViewDrop.h"
#include <PolyLinesItem.h>

/**
* @brief Default constructor
*/
GraphicsViewDrop::GraphicsViewDrop(QWidget *parent) : QGraphicsView(parent)
{
  click = 0;
  setAcceptDrops(true);
}

/**
* @brief Constructor with scene
* @param scene The current scene
*/
GraphicsViewDrop::GraphicsViewDrop(QGraphicsScene * scene, QWidget * parent) : 
                        QGraphicsView(scene,parent)
{
  click = 0;
  setAcceptDrops(true);
}

/**
* @brief Set Table of shared resources for render the icons
* @param render Pointer to the table 
*/
void GraphicsViewDrop::setRedererTable(QHash<QString,QSvgRenderer *> *render)
{
  if(render)
    rendererTable = render;
}

/**
* @brief Drop event when the item is drop in the scene
* @param event The event
*/
void GraphicsViewDrop::dropEvent(QDropEvent * event)
{
  if (event->mimeData()->hasText()) 
  {
    QString name = event->mimeData()->text();
    SvgDraggableItem *svgItem = new SvgDraggableItem();
    svgItem->setSharedRenderer(rendererTable->value(name));
    scene()->addItem(svgItem);
    svgItem->setScale(0.5);
    qDebug() << "Pos in View Coordinates : " << event->pos();
    qDebug() << "Pos in Scene Coordinate: " << mapToScene(event->pos());
    svgItem->setPosToItem(mapToScene(event->pos()));                                        //!!!
    event->accept();
  } 
  else 
      event->ignore();
}


void GraphicsViewDrop::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasText()) 
  {
    event->setDropAction(Qt::MoveAction);
    event->accept();
  } 
  else
    event->ignore();
}

void GraphicsViewDrop::dragMoveEvent(QDragMoveEvent *event)
{
  if (event->mimeData()->hasText()) 
  {
    event->setDropAction(Qt::MoveAction);
    event->accept();
  } 
  else 
    event->ignore();
}

/**
* @brief Function to handle 
* @param event The event
*/
void GraphicsViewDrop::mouseDoubleClickEvent(QMouseEvent * event)
{
  QPoint p = event->pos();
  qDebug() <<"Point" <<p;
  qDebug()  <<"CLicks = " << click;
  SvgDraggableItem * item = static_cast<SvgDraggableItem *>(itemAt(p));
  if(item)
  {
    click++;
    if( click == 2)
    {
      PolyLinesItem *wire = new PolyLinesItem(first,item,mapToScene(init),mapToScene(p));
      scene()->addItem(wire);
      first->addWire(wire,true);
      item->addWire(wire,false);
      click = 0;
    }
    else if( click == 1)
    {
      init = p;
      first = item;
    }
  }
  else
  {
    click = 0;
    first = 0;
  }
  
  qDebug() << "Pos in View Coordinates : " << event->pos();
  qDebug() << "Pos in Scene Coordinate: " << mapToScene(event->pos());
  QGraphicsView::mouseDoubleClickEvent(event);

}

void GraphicsViewDrop::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
  if (factor < 0.07 || factor > 100)
    return;

  scale(scaleFactor, scaleFactor);
}

void GraphicsViewDrop::zoomIn()
{
  scaleView(qreal(1.2));
}

void GraphicsViewDrop::zoomOut()
{
  scaleView(1 / qreal(1.2));
}

void GraphicsViewDrop::wheelEvent(QWheelEvent *event)
{
  scaleView(pow((double)2, event->delta() / 240.0));
}
