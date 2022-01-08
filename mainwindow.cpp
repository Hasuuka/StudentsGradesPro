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

    m_thread = new DownloadThread();
    connect(m_thread,SIGNAL(hello()), this, SLOT(doSomething()));





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
    //emit informButton();


    m_thread->start();

    qDebug() << "Thread: " << m_thread->currentThread() << " started.";
    m_thread->wait(); // Wait for end of thread

    qDebug() << "thread: " << m_thread->currentThread() << " is finished";

    m_thread->quit();

    m_csvListModel = new CsvListModel(SharedData::instance()->csvs(), this);
    ui->csvList->setModel(m_csvListModel);

    delete m_thread;
}

void MainWindow::changeUrl(QString url)
{
    m_url = url;
    if(!m_url.isEmpty()){
        ui->calculateButton->setDisabled(false);
    }
    qDebug()<< m_url;
}

void MainWindow::changeButton()
{
    ui->cancelButton->setDisabled(false);
}


void MainWindow::on_cancelButton_clicked()
{
    qDebug()<< "quitted";
    if(m_thread->isRunning()){
        m_thread->requestInterruption();
    }

}

void MainWindow::doSomething()
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this , [&](QNetworkReply *reply){
        QByteArray data = reply ->readAll();
         QString str = QString::fromLatin1(data);
         qDebug() << str;
    });
    manager->get(QNetworkRequest(QUrl("https://codingprof.hs-rw.de/files/exercise-files/filelist.txt")));
}

