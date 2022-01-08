#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shareddata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_csvListModel = new CsvListModel(SharedData::instance()->csvs(), this);
    ui->csvList->setModel(m_csvListModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

