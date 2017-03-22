#include <PolyLinesItem.h>

/**
* @brief Default constructor 
*/
PolyLinesItem::PolyLinesItem(QGraphicsItem *parent) : 
                                                QGraphicsPathItem(parent) 
{
  setFlags(QGraphicsItem::ItemIsSelectable);
}

/**
* @brief Constructor with points
* @param start Start Point in Scene coordinates
* @param end  End Point in Scene coordinates
*/
PolyLinesItem::PolyLinesItem(SvgDraggableItem *fItem,SvgDraggableItem *lItem
                  ,const QPointF &start, const QPointF &end ,
                    QGraphicsItem* parent ) : QGraphicsPathItem(parent) 
{
  setFlags(QGraphicsItem::ItemIsSelectable);
  penWidth = 2;
  color = Qt::black;
  firstItem = fItem;
  lastItem = lItem;
  qDebug() << "MapToScene >> (" << start << "," << end <<")";
  adjust(start,end);
  qDebug() << "Points in PolyLInes " << breakPoints ;
}

/**
* @brief Calculate de intermediate points for the polyLine
* @param start Start Point in Scene coordinates
* @param end  End Point in Scene coordinates
*/
void PolyLinesItem::CalculatePoints(const QPointF &start, const QPointF &end)
{
  breakPoints.clear();
  if(start.x() < end.x())
  {
    breakPoints.push_back(start);
    int midX =  (end.x()+start.x())/2;
    breakPoints.push_back(QPoint(midX,start.y()));
    breakPoints.push_back(QPoint(midX,end.y()));
    breakPoints.push_back(end);
  }
  else
  {
    breakPoints.push_back(start);
    int midY = (end.y()+start.y())/2;
    breakPoints.push_back(QPoint(start.x(),midY));
    breakPoints.push_back(QPoint(end.x(),midY));
    breakPoints.push_back(end);
  }
}

void PolyLinesItem::adjust(const QPointF &start, const QPointF &end)
{
  CalculatePoints(start,end);
  prepareGeometryChange();
  QPainterPath mpath(start);
  mpath.lineTo(QPointF(breakPoints.at(1)));
  mpath.lineTo(QPointF(breakPoints.at(2)));
  mpath.lineTo(QPointF(breakPoints.at(3)));
  path = mpath;
  setPath(path);
}


QPointF PolyLinesItem::firstPoint() const
{
  return breakPoints.at(0);
}

QPointF PolyLinesItem::lastPoint() const
{
  return breakPoints.at(3);
}

bool PolyLinesItem::detach()
{
  firstItem->removeWire(this);
  lastItem->removeWire(this);
  return true;
}
/**
* @brief Changue the color to item selected
* @param event The Event
*/
void PolyLinesItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  color = Qt::red;
  update();
  //QGraphicsPathItem::mousePressEvent(event);
}

/**
* @brief Paint the polyLines in the Scene
* @param painter Painter
*/
void PolyLinesItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
  painter->setPen(QPen(color, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
  painter->drawPath(path);
}


int PolyLinesItem::type() const
{
  return Type;
}