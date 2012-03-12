#ifndef OPENFILESDIALOG_H
#define OPENFILESDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class OpenFilesDialog;
}

class OpenFilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFilesDialog(QWidget *parent = 0);
    ~OpenFilesDialog();


private slots:
    void on_m_pButtonFilePathLeft_clicked();
    void on_m_pButtonFilePathRight_clicked();

private:
    Ui::OpenFilesDialog *ui;

    static QString stripFilePath(QString str);

public:
    QString getLeftFilePath();
    QString getRightFilePath();
};

#endif // OPENFILESDIALOG_H
