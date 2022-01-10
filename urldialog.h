#ifndef URLDIALOG_H
#define URLDIALOG_H

#include <QDialog>

namespace Ui {
class urlDialog;
}

class urlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit urlDialog(QWidget *parent = nullptr);
    ~urlDialog();
    QString url()const;

signals:
    void urlChanged(QString url);

private:
    Ui::urlDialog *ui;
};

#endif // URLDIALOG_H
