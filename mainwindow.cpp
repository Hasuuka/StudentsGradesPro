#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shareddata.h"
#include "QDebug"
#include "downloadthread.h"
#include "urldialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_csvListModel = new CsvListModel(SharedData::instance()->csvs(), this);
    ui->csvList->setModel(m_csvListModel);

    ui->calculateButton->setDisabled(true);
    ui->cancelButton->setDisabled(true);

    connect(this, &MainWindow::informUrl, this, &MainWindow::changeUrl);
    connect(this, &MainWindow::informButton, this, &MainWindow::changeButton);

    m_thread = new QThread();
    m_download = new Download();

    connect(m_download, &Download::downloadFinished, this, &MainWindow::downloadFinished);
    connect(m_download, &Download::progressUpdated, this, &MainWindow::progressUpdated);
    m_download->moveToThread(m_thread);

}


MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_downloadButton_clicked()
{
    urlDialog dlg;
    if(dlg.exec()==QDialog::Accepted){

        emit informUrl(dlg.url());
    }
}


void MainWindow::on_calculateButton_clicked()
{
    emit informButton();
    m_thread->start();
    QMetaObject::invokeMethod(m_download,"startCalculation");
}

void MainWindow::changeUrl(QString url)
{
    m_url = url;
    if(!m_url.isEmpty()){
        ui->calculateButton->setDisabled(false);
    }
    qDebug() << m_url;
}

void MainWindow::changeButton()
{
    ui->cancelButton->setDisabled(false);
}

void MainWindow::downloadFinished()
{

}

void MainWindow::progressUpdated()
{

}

void MainWindow::updateCsvList()
{
    m_csvListModel = new CsvListModel(SharedData::instance()->csvs(), this);
    ui->csvList->setModel(m_csvListModel);
}


void MainWindow::on_cancelButton_clicked()
{
    if(m_thread->isRunning()){
        m_thread->requestInterruption();
        m_thread->quit();
        m_thread->wait();
        delete m_thread;
        delete m_download;
        qDebug()<< "quitted";
    }

}


