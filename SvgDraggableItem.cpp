#include "SvgDraggableItem.h"

SvgDraggableItem::SvgDraggableItem(QGraphicsItem* parent):
    QGraphicsSvgItem(parent), m_dragged(false)
{
    setFlags(QGraphicsItem::ItemIsSelectable|
             QGraphicsItem::ItemIsMovable);
}

void SvgDraggableItem::setAnchorPoint(const QPointF &anchorPoint){
    this->anchorPoint = anchorPoint;
}
void SvgDraggableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    m_dragged = true;
    QGraphicsSvgItem::mouseMoveEvent(event);
}

void SvgDraggableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "=====================";
    qDebug() <<"ScenePos : "<<    event->scenePos();
    qDebug() << "Item Coordinates " << event->pos();
    qDebug() << "Item Pos : " << this->mapFromScene(event->scenePos());
    QRectF b = boundingRect();
    qDebug() <<"boundingRect "<< b;
    QPointF p = event->pos() - QPointF(b.width()/2.0,b.height()/2.0);
    qDebug() << "PointF: " <<p;
    if(m_dragged){
        
        this->setPos(mapToScene(p));
        m_dragged = false;
    }

    update();
    QGraphicsSvgItem::mouseReleaseEvent(event);
}

void SvgDraggableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      update();
      QGraphicsSvgItem::mouseReleaseEvent(event);  
}

void SvgDraggableItem::setPosToItem(const QPointF &p)
{
    QRectF b = boundingRect();
    this->setPos(p-QPointF(b.width()/4.0,b.height()/4.0));
}