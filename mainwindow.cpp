#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shareddata.h"
#include "QDebug"
#include "urldialog.h"
#include "string"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_csvListModel = new CsvListModel(SharedData::instance()->csvs(), this);
    ui->csvList->setModel(m_csvListModel);

    ui->calculateButton->setDisabled(true);
    ui->cancelButton->setDisabled(true);
    ui->progressBar->setValue(0);

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
    delete m_thread;
    delete m_download;
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
    ui->calculateButton->setDisabled(true);
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
    ui->cancelButton->setDisabled(true);
    ui->calculateButton->setDisabled(false);

    m_thread->quit();
    m_thread->wait();
}

void MainWindow::progressUpdated(int value, int maximum)
{
    ui->progressBar->setMaximum(maximum);
    value+= ui->progressBar->value();
    ui->progressBar->setValue(value);
    int progress =static_cast<float>(static_cast<float>(value/static_cast<float>(maximum)))*static_cast<float>(100);
    ui->label->setText("Progess " + QString::fromStdString(to_string(progress)) + "%"+ " of 100%");
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
        qDebug()<< "Thread quitted";
        ui->cancelButton->setDisabled(true);
        ui->calculateButton->setDisabled(false);
        ui->progressBar->setValue(0);
        ui->label->setText("Progess 0% of 100%");

    }
}


