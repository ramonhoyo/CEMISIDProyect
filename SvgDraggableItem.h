#ifndef SVGDRAGGABLEITEM_H
#define SVGDRAGGABLEITEM_H
#include <QtGui>
#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>


class SvgDraggableItem : public QGraphicsSvgItem
{
public:
    SvgDraggableItem(QGraphicsItem* parent = 0);
    void setAnchorPoint(const QPointF& anchorPoint);
    void setPosToItem(const QPointF &);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QPointF anchorPoint;
    bool m_dragged;
};

#endif
