#include "GraphicsViewDrop.h"
#include <SvgDraggableItem.h>

GraphicsViewDrop::GraphicsViewDrop(QWidget *parent) : QGraphicsView(parent)
{
    setAcceptDrops(true);
}

GraphicsViewDrop::GraphicsViewDrop(QGraphicsScene * scene, QWidget * parent) : 
                        QGraphicsView(scene,parent)
{
    setAcceptDrops(true);
}

void GraphicsViewDrop::setRedererTable(QHash<QString,QSvgRenderer *> *render)
{
    rendererTable = render;
}

void GraphicsViewDrop::dropEvent(QDropEvent * event)
{
        if (event->mimeData()->hasText()) 
        {
            QString name = event->mimeData()->text();
            SvgDraggableItem *svgItem = new SvgDraggableItem();
            svgItem->setSharedRenderer(rendererTable->value(name));
            scene()->addItem(svgItem);
            svgItem->setPos(event->pos());
            svgItem->setScale(0.5);
            event->accept();
        } 
        else 
        {
            event->ignore();
        }
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