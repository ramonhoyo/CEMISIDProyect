#include "SvgDraggableItem.h"
#include <PolyLinesItem.h>
#include <GraphicsViewDrop.h>

SvgDraggableItem::SvgDraggableItem(QGraphicsItem* parent):
    QGraphicsSvgItem(parent), m_dragged(false)
{
  setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
}

void SvgDraggableItem::setAnchorPoint(const QPointF &anchorPoint)
{
  this->anchorPoint = anchorPoint;
}
void SvgDraggableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  qDebug() << "Move: " << event->scenePos() ;
  m_dragged = true;
  QPair<bool,PolyLinesItem *> curr;
  qDebug() << wireLines.size();
  foreach (curr , wireLines)
  {
      PolyLinesItem *wire = curr.second;
      if(curr.first)
        wire->adjust(QPointF(event->scenePos()),wire->lastPoint());
      else
        wire->adjust(wire->firstPoint(),QPointF(event->scenePos()));
  }
  QGraphicsSvgItem::mouseMoveEvent(event);
}

void SvgDraggableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  //qDebug() << "=====================";
  //qDebug() <<"ScenePos : "<<    event->scenePos();
  //qDebug() << "Item Coordinates " << event->pos();
  //qDebug() << "Item Pos : " << this->mapFromScene(event->scenePos());
  QRectF b = boundingRect();
  QPointF p = event->pos() - QPointF(b.width()/2.0,b.height()/2.0);
  if(m_dragged)
  {
    this->setPos(mapToScene(p));
    m_dragged = false;
  }

  update();
  QGraphicsSvgItem::mouseReleaseEvent(event);
}

void SvgDraggableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  qDebug() <<"Cantidad de Lineas:  " << wireLines.size();
  update();
  QGraphicsSvgItem::mouseReleaseEvent(event);  
}

/**
* @brief Set item in the point with center in the middle of the Item.
* @param p Point in Scene coordinates
*/
void SvgDraggableItem::setPosToItem(const QPointF &p)
{
  QRectF b = boundingRect();
  QPointF middlePoint = (QPointF(b.width(),b.height())/2.0)*scale();
  this->setPos(p-middlePoint);
}

 void SvgDraggableItem::addWire(PolyLinesItem *wire,bool out)
 {
    wireLines << QPair<bool,PolyLinesItem*>(out,wire);
 }

 bool SvgDraggableItem::removeWire(PolyLinesItem *wire)
 {
    QPair<bool,PolyLinesItem*> removedWire;
    int found = -1;
    int i = 0;
    foreach(removedWire, wireLines)
    {
      if(removedWire.second == wire)
      {
        found = i;
        break;
      }
      i++;
    }
      
    qDebug() <<"found == "<< found;
    if(found >= 0)
    {
      wireLines.removeAt(found);
      qDebug() << "FOund : " << wireLines.size();
      return true;
    }
    
    return false;
 }

 void SvgDraggableItem::deleteAllWires(QGraphicsScene *scene)
 {
    while(!wireLines.isEmpty())
    {
      PolyLinesItem *removedWire = wireLines.takeFirst().second;
      qDebug() << "detach() ";
      removedWire->detach();
      scene->removeItem(removedWire);
      delete removedWire;
    }
 }

 int SvgDraggableItem::type() const
 {
    return Type;
 }