#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <MGraphicsScene.h>
#include <SvgDraggableItem.h>
#include <PolyLinesItem.h>
#include <QHash>
#include <frameDrag.h>
#include <GraphicsViewDrop.h>
#include <QSplitter>
#include <QToolBar>
enum class ACTION
{
  ADDGATE ,
  ADDSIGNAL ,
  ADDPIN
};


class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);

/*
   *  aqui el enfoque es , que dado un mousePressEvent , se verifique el estado de la
   *  variable action , la cual tiene es un enum class cuyos estados son ADDGATE ,
   *  ADDSIGNAL Y ADDPIN (por ahora), luego que se conoce el estado llamar al metodo
   *  correspondiente , addGate(), addSignal() o addPin() , falta definir estos metodos
   *  realizar o que se debe hacer .
   *
   *  de resto lo que agrege fue el enum class , un toolbar , las acciones y realice los
   *  metodos para que nunca hayan dos acciones seleccionadas .
   *
   * si no te compila es por lo que cambie donde hacias include <QtWidgets> por
   * include <QtGui>
   *
*/
public slots:
  void addGate();
  void addSignal();
  void addPin();

private:
  MGraphicsScene *scene;
  GraphicsViewDrop *view;
  QSplitter *sp;
  QHash<QString,QSvgRenderer *> rendererTable;
  frameDrag *frame;
  ACTION action;
  QToolBar *barActions;
  QAction *addGateAction , *addSignalAction , *addPinAction;
private slots:
  void createToolBars();
  void createActionsPrivate();
  void changeToAddGateMode();
  void changeToAddSignalMode();
  void changeToAddPinMode();

protected:
  void keyPressEvent(QKeyEvent * event);
  void resizeEvent(QResizeEvent * event);

};

#endif
