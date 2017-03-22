#include "MainWindow.h"
#include <QtSvg/QSvgRenderer>
#include <QKeyEvent>
#include <QToolBar>
#include <QAction>
#include <QMenu>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  createActionsPrivate();
  createToolBars();
  this->action = ACTION::ADDGATE;

  scene = new MGraphicsScene();
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
  QLatin1String text("Press Delete and select a item to detele\n"
                     "Select Multiples Items pressing on ctrl");
  scene->addText(text,f);

}

void MainWindow::addGate()
{

}

void MainWindow::addSignal()
{

}

void MainWindow::addPin()
{

}

void MainWindow::createToolBars()
{
  barActions = new QToolBar();

  barActions->addAction(addGateAction);
  barActions->addAction(addSignalAction);
  barActions->addAction(addPinAction);
  barActions->setMovable(false);

  this->addToolBar(barActions);
}

void MainWindow::createActionsPrivate()
{
  addGateAction = new QAction(tr("add gate"),this);
  addGateAction->setCheckable(true);
  connect(addGateAction, SIGNAL(triggered()), this, SLOT(changeToAddGateMode()));
  addGateAction->setChecked(true);

  addSignalAction = new QAction(tr("add action"),this);
  addSignalAction->setCheckable(true);
  connect(addSignalAction, SIGNAL(triggered()), this, SLOT(changeToAddSignalMode()));

  addPinAction = new QAction(tr("add pin"),this);
  addPinAction->setCheckable(true);
  connect(addPinAction, SIGNAL(triggered()), this, SLOT(changeToAddPinMode()));

}

void MainWindow::changeToAddGateMode()
{
 if(addPinAction->isChecked())
   addPinAction->setChecked(false);
 if(addSignalAction->isChecked())
   addSignalAction->setChecked(false);
 this->action = ACTION::ADDGATE;
 return;
}

void MainWindow::changeToAddSignalMode()
{
  if(addGateAction->isChecked())
    addGateAction->setChecked(false);
  if(addPinAction->isChecked())
    addPinAction->setChecked(false);
  this->action = ACTION::ADDSIGNAL;
  return;
}

void MainWindow::changeToAddPinMode()
{
  if(addGateAction->isChecked())
    addGateAction->setChecked(false);
  if(addSignalAction->isChecked())
    addSignalAction->setChecked(false);
  this->action = ACTION::ADDPIN;
  return;
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
        if(item)
        {
          PolyLinesItem *wire = qgraphicsitem_cast<PolyLinesItem *>(item);
          if(wire != 0)
          {
            qDebug() << "WIRE >>>";
            wire->detach();
            qDebug() << "Wire Delete";
          }
          else
          {
            qDebug() << "SvgDraggableItem";
            qgraphicsitem_cast<SvgDraggableItem*>(item)->deleteAllWires(scene);
          }
          scene->removeItem(item);
          delete item;
        }
      }
    }
  }

  switch(event->key())
  {
  case Qt::Key_Escape:
    close();
    break;
  case  Qt::Key_Plus:
    view->zoomIn();
    break;
  case Qt::Key_Minus:
    view->zoomOut();
    break;
  default:
    QMainWindow::keyPressEvent(event);
  }
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
  QSize nSize = event->size();
  scene->setSceneRect(QRectF(QPointF(0.0,0.0),QSizeF(nSize)));
}
