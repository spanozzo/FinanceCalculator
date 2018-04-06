#include "view_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), cp(new ControllerPortfolio(this)) {
  ui->setupUi(this);
  ct = new CalculatorTab(ui->calcolatriceTab, cp);
  pt = new PortfolioTab(ui->portfolioTab, cp);
  ui->portfolioTab->setLayout(new QGridLayout());
  ui->portfolioTab->layout()->addWidget(pt);
  ui->calcolatriceTab->setLayout(new QGridLayout());
  ui->calcolatriceTab->layout()->addWidget(ct);

  connect(this, SIGNAL(remove_assetnTable_sig(int)), pt, SLOT(remove_tableRow_portfolio(int)));
  connect(this, SIGNAL(remove_assetnTable_sig(int)), ct, SLOT(remove_tableRow_calculator(int)));
  connect(this, SIGNAL(add_tableRow_sig(QString,QString,double,double,uint,double,double,bool,bool,uint)),
          pt, SLOT(add_tableRow_portfolio(QString,QString,double,double,uint,double,double,bool,bool,uint)));
  connect(this, SIGNAL(add_tableRow_sig(QString,QString,double,double,uint,double,double,bool,bool,uint)),
          ct, SLOT(add_tableRow_calculator(QString,QString,double,double,uint,double,double,bool,bool,uint)));
}
MainWindow::~MainWindow() {
  delete ui;
  delete cp;
  delete ct;
  delete pt;
}

void MainWindow::remove_asset_gui(int n) {
  emit remove_assetnTable_sig(n);
}

void MainWindow::add_tableRow_s(QString rType, QString rName, double rPrice, double rSellPrice, uint rUnit,
                                double rDividend, double rCoupon, bool rState, bool rShort, uint rLeva) {
  emit add_tableRow_sig(rType, rName, rPrice, rSellPrice, rUnit, rDividend, rCoupon, rState, rShort, rLeva);
}
