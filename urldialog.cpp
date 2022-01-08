#include "urldialog.h"
#include "ui_urldialog.h"

urlDialog::urlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::urlDialog)
{
    ui->setupUi(this);
}

urlDialog::~urlDialog()
{
    delete ui;
}

QString urlDialog::url() const
{
    return ui->urlLineEdit->text();
}
