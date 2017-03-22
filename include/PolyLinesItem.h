#ifndef POLYLINESITEM_H
#define POLYLINESITEM_H
#include <QtGui>
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <SvgDraggableItem.h>

/**
* @brief Class for implement PolyLines in the scene
* @param event The event
*/
class PolyLinesItem : public QGraphicsPathItem
{
  public:
    enum { Type = UserType + 2 };

    PolyLinesItem(QGraphicsItem* parent = 0);
    PolyLinesItem(SvgDraggableItem *fItem, SvgDraggableItem *lItem,
       const QPointF &start, const QPointF &end,QGraphicsItem* parent = 0);
    int type() const;
    QPointF firstPoint() const;
    QPointF lastPoint() const;
    void adjust(const QPointF &start, const QPointF &end);
    bool detach();
  protected:
   void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
  private:
    QVector<QPointF> breakPoints;
    int penWidth;
    QPainterPath path;
    QColor color;
    SvgDraggableItem *firstItem;
    SvgDraggableItem *lastItem;
  private:
    void CalculatePoints(const QPointF &start, const QPointF &end);
};

#endif
