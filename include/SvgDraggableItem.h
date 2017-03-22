#ifndef SVGDRAGGABLEITEM_H
#define SVGDRAGGABLEITEM_H
#include <QtGui>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QPair>

class PolyLinesItem;
/**
* @brief Class for represent a item in with icon in format .svg
*/
class SvgDraggableItem : public QGraphicsSvgItem
{
  public:
    enum { Type = UserType + 1 };

    SvgDraggableItem(QGraphicsItem* parent = 0);
    void setAnchorPoint(const QPointF& anchorPoint);
    int type() const;
    void setPosToItem(const QPointF &);
    void addWire(PolyLinesItem *wire, bool out);
    bool removeWire(PolyLinesItem *wire);
    void deleteAllWires(QGraphicsScene *scene);
  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
  private:
    QPointF anchorPoint;
    QList<QPair<bool,PolyLinesItem*> > wireLines; 
    bool m_dragged;
};

#endif
