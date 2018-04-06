// PANOZZO STEFANO - MATRICOLA 1097068

#include "view_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow financeCalc;
  financeCalc.show();

  return app.exec();
}
