#include "view_calculator.h"

CalculatorTab::CalculatorTab(QWidget *parent, ControllerPortfolio* c): QWidget(parent), ui(new Ui::view_calculator), cp(c) {
  ui->setupUi(this);

  ui->calculator_tableWidget->setColumnCount(10);
  ui->calculator_tableWidget->setHorizontalHeaderLabels(QStringList() << "Tipo" << "Nome" << "Prezzo" << "Pr.Vendita" << "Unità" << "Dividendo" << "Cedola" << "Bond Gov." << "Short" << "Leva");
  for(int c=0; c < ui->calculator_tableWidget->horizontalHeader()->count(); ++c)
    ui->calculator_tableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
  ui->secondOp_spinBox->setMaximum(0);
  ui->result_LCD->setAutoFillBackground(true);
  connect(this, SIGNAL(result_sig(double)), ui->result_LCD, SLOT(display(double)));
  connect(ui->taxOn_checkBox, SIGNAL(clicked(bool)), cp, SLOT(change_tax_s(bool)));
  connect(this, SIGNAL(union_assets_sig(int,int)), cp, SLOT(union_assets_s(int,int)));
  connect(ui->calculator_tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(change_maxUnit_s(int,int)));
  na = new QIcon(":/icon/icone/not_available.png");
  checked = new QIcon(":/icon/icone/checked.png");
  notChecked = new QIcon(":/icon/icone/notChecked.png");
}
CalculatorTab::~CalculatorTab() {
  delete ui;
  delete na;
  delete checked;
  delete notChecked;
}

void CalculatorTab::add_tableRow_calculator(QString dType, QString dName, double dPrice, double dSellPrice, uint dUnit,
                                double dDividend, double dCoupon, bool dState, bool dShort, uint dLeva) {

  ui->calculator_tableWidget->insertRow(ui->calculator_tableWidget->rowCount());
  QTableWidgetItem* tType = new QTableWidgetItem(dType);
  QTableWidgetItem* tName = new QTableWidgetItem(dName);
  QTableWidgetItem* tPrice = new QTableWidgetItem(QString::number(dPrice));
  QTableWidgetItem* tSellPrice = new QTableWidgetItem(QString::number(dSellPrice));
  QTableWidgetItem* tUnit = new QTableWidgetItem(QString::number(dUnit));
  QTableWidgetItem* tDividend, * tCoupon, * tStateBond, * tShortSell, * tLeverage;

  if(dType == "Stock") {
    tDividend = new QTableWidgetItem(QString::number(dDividend));
    tCoupon = new QTableWidgetItem(*na, 0);
    tStateBond = new QTableWidgetItem(*na, 0);
    tShortSell = new QTableWidgetItem(*na, 0);
    tLeverage = new QTableWidgetItem(*na, 0);
  }
  else {
    if(dType == "Bond") {
      tDividend = new QTableWidgetItem(*na, 0);
      tCoupon = new QTableWidgetItem(QString::number(dCoupon));
      tShortSell = new QTableWidgetItem(*na, 0);
      tLeverage = new QTableWidgetItem(*na, 0);
      if(dState)
        tStateBond = new QTableWidgetItem(*checked, 0);
      else
        tStateBond = new QTableWidgetItem(*notChecked, 0);
    }
    else {
      tDividend = new QTableWidgetItem(*na, 0);
      tCoupon = new QTableWidgetItem(*na, 0);
      tStateBond = new QTableWidgetItem(*na, 0);
      tLeverage = new QTableWidgetItem(QString::number(dLeva));
      if(dShort)
        tShortSell = new QTableWidgetItem(*checked, 0);
      else
        tShortSell = new QTableWidgetItem(*notChecked, 0);
    }
  }
  int n = ui->calculator_tableWidget->rowCount();
  ui->calculator_tableWidget->setItem(n-1, 0, tType);
  ui->calculator_tableWidget->setItem(n-1, 1, tName);
  ui->calculator_tableWidget->setItem(n-1, 2, tPrice);
  ui->calculator_tableWidget->setItem(n-1, 3, tSellPrice);
  ui->calculator_tableWidget->setItem(n-1, 4, tUnit);
  ui->calculator_tableWidget->setItem(n-1, 5, tDividend);
  ui->calculator_tableWidget->setItem(n-1, 6, tCoupon);
  ui->calculator_tableWidget->setItem(n-1, 7, tStateBond);
  ui->calculator_tableWidget->setItem(n-1, 8, tShortSell);
  ui->calculator_tableWidget->setItem(n-1, 9, tLeverage);
  for(int i=0; i < ui->calculator_tableWidget->columnCount() ; ++i)
    ui->calculator_tableWidget->item(n-1, i)->setFlags(ui->calculator_tableWidget->item(n-1, i)->flags() & ~Qt::ItemIsEditable);
  ui->secondOp_spinBox->setMinimum(1);
  ui->secondOp_spinBox->setMaximum(ui->calculator_tableWidget->rowCount());
}
void CalculatorTab::remove_tableRow_calculator(int n) {
  ui->calculator_tableWidget->removeRow(n);
  ui->secondOp_spinBox->setMaximum(ui->calculator_tableWidget->rowCount());
}
int CalculatorTab::getRow() const {
  QModelIndexList selectedRow = ui->calculator_tableWidget->selectionModel()->selectedRows();
  return (selectedRow.first().row());
}
bool CalculatorTab::checkSelect() const {
  if(ui->calculator_tableWidget->selectionModel()->selectedRows().count() == 0) {
    QMessageBox *msg = new QMessageBox();
    msg->setWindowTitle("Attenzione!");
    msg->setText("Nessuna riga selezionata!");
    msg->show();
    return false;
  }
  return true;
}

void CalculatorTab::on_gain_pushButton_clicked() {
  if(checkSelect()) {
    if(preAdd)
      preAdd = false;
    int u = ui->unita_spinBox->value();
    int n = getRow();
    emit result_sig(cp->getGain(n, u));
  }
}

void CalculatorTab::on_gainDividendo_pushButton_clicked() {
  if(checkSelect()) {
    if(preAdd)
      preAdd = false;
    int n = getRow();
    if(ui->calculator_tableWidget->item(n, 0)->text() == "Stock")
      emit result_sig(cp->getDividendGain(n));
    else {
      QMessageBox* msg = new QMessageBox();
      msg->setWindowTitle("Messaggio");
      msg->setText("Questa funzione è disponibile solo per asset di tipo Stock.");
      msg->show();
    }
  }
}

void CalculatorTab::on_totalGain_pushButton_clicked() {
  if(checkSelect()) {
    if(preAdd)
      preAdd = false;
    int n = getRow();
    emit result_sig(cp->getTotalGain(n));
  }
}

void CalculatorTab::on_ROI_pushButton_clicked() {
  if(checkSelect()) {
    if(preAdd)
      preAdd = false;
    int n = getRow();
    emit result_sig(cp->getROI(n));
  }
}

void CalculatorTab::on_gainCedola_pushButton_clicked() {
  if(checkSelect()) {
    if(preAdd)
      preAdd = false;
    int n = getRow();
    if(ui->calculator_tableWidget->item(n,0)->text() == "Bond")
      emit result_sig(cp->getCouponGain(n));
    else {
      QMessageBox* msg = new QMessageBox();
      msg->setWindowTitle("Messaggio");
      msg->setText("Questa funzione è disponibile solo per asset di tipo Bond.");
      msg->show();
    }
  }
}

void CalculatorTab::on_add_pushButton_clicked() {
  if(checkSelect()) {
    int n = getRow();
    if(n != (ui->secondOp_spinBox->value()-1)) {
      if(preAdd) {
        double preRis = ui->result_LCD->value();
        emit result_sig(cp->getAdd(preRis, ui->secondOp_spinBox->value()-1));
      }
      else {
        emit result_sig(cp->getAdd(n, ui->secondOp_spinBox->value()-1));
        preAdd = true;
      }
    }
    else {
      QMessageBox *msg=new QMessageBox();
      msg->setWindowTitle("Attenzione!");
      msg->setText("Stai sommando un asset con se stesso.\nSeleziona un asset differente da 'Secondo Operando'");
      msg->show();
    }
  }
}

void CalculatorTab::on_differenceGain_pushButton_clicked() {
  if(checkSelect()) {
    if(preAdd)
      preAdd = false;
    int n = getRow();
    if(n == (ui->secondOp_spinBox->value()-1)) {
      QMessageBox *msg=new QMessageBox();
      msg->setWindowTitle("Attenzione!");
      msg->setText("I due assets su cui eseguire l'operazione coincidono.\nSeleziona un asset differente da 'Secondo Operando'");
      msg->show();
    }
    else
      emit result_sig(cp->getDiffGain(n, ui->secondOp_spinBox->value()-1));
  }
}

void CalculatorTab::on_union_pushButton_clicked() {
  if(checkSelect()) {
    if(preAdd)
      preAdd = false;
    int n = getRow();
    int k = ui->secondOp_spinBox->value()-1;
    int size = cp->getSize();
    if(n == k) {
      QMessageBox *msg=new QMessageBox();
      msg->setWindowTitle("Attenzione!");
      msg->setText("I due assets su cui eseguire l'operazione coincidono.\nSeleziona un asset differente da 'Secondo Operando'");
      msg->show();
    }
    else {
      emit union_assets_sig(n, k);
      if(cp->getSize() == size) {
        // nessuna unione avvenuta --> asset non compatibili
        QMessageBox *msg=new QMessageBox();
        msg->setWindowTitle("Attenzione!");
        msg->setText("I due assets su cui eseguire l'operazione non sono compatibili.\nSeleziona un asset differente da 'Secondo Operando'");
        msg->show();
      }
    }
  }
}

void CalculatorTab::change_maxUnit_s(int n, int) {
  int maxUnit = ui->calculator_tableWidget->item(n, 4)->text().toInt();
  ui->unita_spinBox->setMaximum(maxUnit);
  ui->unita_spinBox->setMinimum(1);
  ui->unita_spinBox->setValue(maxUnit);
  if(preAdd)
    preAdd = false;
}

void CalculatorTab::on_valTotale_pushButton_clicked() {
  if(ui->calculator_tableWidget->rowCount() == 0)
    emit result_sig(0);
  else
    emit result_sig(cp->getTotalReturn());
}

void CalculatorTab::on_pushButton_clicked()  {
  if(ui->calculator_tableWidget->rowCount() == 0)
    emit result_sig(0);
  else
    emit result_sig(cp->getGainPortfolio());
}
