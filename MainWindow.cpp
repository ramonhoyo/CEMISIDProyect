#include "MainWindow.h"
#include <QSvgRenderer>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,480,360);
    frame = new frameDrag();
    frame->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    frame->resize(100,360);
    view = new GraphicsViewDrop(scene);
    setAcceptDrops(true);

    sp = new QSplitter();
    sp->addWidget(frame);
    sp->addWidget(view);
    setCentralWidget(sp);
    QBrush myBrush(Qt::blue, Qt::CrossPattern);
    view->setBackgroundBrush(myBrush);

    resize(580,360);
    //Resources table for shared svg files
    rendererTable.insert(QString("AND_gate"),new QSvgRenderer(QLatin1String(":/SVG/AND_gate.svg")));
    rendererTable.insert(QString("OR_gate"),new QSvgRenderer(QLatin1String(":/SVG/OR_gate.svg")));
    rendererTable.insert(QString("XOR_gate"),new QSvgRenderer(QLatin1String(":/SVG/XOR_gate.svg")));
    rendererTable.insert(QString("NOT_gate"),new QSvgRenderer(QLatin1String(":/SVG/NOT_gate.svg")));

    view->setRedererTable(&rendererTable);

    SvgDraggableItem *svgItem = new SvgDraggableItem();
    svgItem->setSharedRenderer(rendererTable.value(QString("AND_gate")));
    scene->addItem(svgItem);
    svgItem->setPos(30,120);
    svgItem->setScale(0.5);

    QFont f("Monospace", -1,QFont::Black);
    QLatin1String text("Press N to add AND_Gate\nPress O to add OR_Gate\n"
                                        "Press Delete and select a item to detele\n"
                                        "Select Multiples Items pressing on ctrl");
    scene->addText(text,f);

}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    if(!items.isEmpty())
    {
        
        qDebug() <<"SelectedItems : "<<scene->selectedItems().size();
        if(event->key() == Qt::Key_Delete)
        {
            while(!items.isEmpty())
            {
                QGraphicsItem *item = items.takeFirst();
                scene->removeItem(item);
                delete item;
            }
        }

        if(event->key() == Qt::Key_X)
        {
             qDebug() << "Cursor " << cursor().pos();
            qDebug() << "mapFromGlobal " << mapFromGlobal(cursor().pos());   
            qDebug() << "Local Item : " << items.first()->mapFromScene(mapFromGlobal(cursor().pos()));  
        }
    }

    // add new item when press the key N (some problems whit the relative positions)
    if(event->key() == Qt::Key_N)
    {
        qDebug() << "Cursor " << view->cursor().pos();
        qDebug() << "mapFromGlobal " << mapFromGlobal(cursor().pos());
        
        SvgDraggableItem *svgItem = new SvgDraggableItem();
        svgItem->setSharedRenderer(rendererTable.value(QString("AND_gate")));
        scene->addItem(svgItem);
        QPointF local = mapFromGlobal(cursor().pos());
        svgItem->setPosToItem(local-QPoint(100,0));
        svgItem->setScale(0.5);
    }

    // Add the OR gate
    if(event->key() == Qt::Key_O)
    {
        SvgDraggableItem *svgItem = new SvgDraggableItem();
        svgItem->setSharedRenderer(rendererTable.value(QString("OR_gate")));
        scene->addItem(svgItem);
        QPointF local = mapFromGlobal(cursor().pos());
        svgItem->setPosToItem(local);
        svgItem->setScale(0.5);
    }

    // only for debug
    if(event->key() == Qt::Key_C)
    {
         qDebug() << "Cursor " << view->cursor().pos();
        qDebug() << "mapFromGlobal " << view->mapFromGlobal(view->cursor().pos());     
    }

    // exit
    if(event->key() == Qt::Key_Escape)
        close();
}