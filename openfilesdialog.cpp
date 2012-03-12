#include "openfilesdialog.h"
#include "ui_openfilesdialog.h"

#include <QFileDialog>

OpenFilesDialog::OpenFilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFilesDialog)
{
    ui->setupUi(this);

    ui->m_pLineEditFilePathLeft->setText("C:\\Projekte\\PD1460\\PD 1460 01.04 Branch\\mmi_text.csv");//("C:\\1.csv");
    ui->m_pLineEditFilePathRight->setText("C:\\2.csv");
}

OpenFilesDialog::~OpenFilesDialog()
{
    delete ui;
}

void OpenFilesDialog::on_m_pButtonFilePathLeft_clicked()
{
    ui->m_pLineEditFilePathLeft->setText(QFileDialog::getOpenFileName(this, "Open CSV-File"));
}

void OpenFilesDialog::on_m_pButtonFilePathRight_clicked()
{
    ui->m_pLineEditFilePathRight->setText(QFileDialog::getOpenFileName(this, "Open CSV-File"));
}

QString OpenFilesDialog::getLeftFilePath()
{
    return stripFilePath(ui->m_pLineEditFilePathLeft->text());
}

QString OpenFilesDialog::getRightFilePath()
{
    return stripFilePath(ui->m_pLineEditFilePathRight->text());

}

QString OpenFilesDialog::stripFilePath(QString str)  {
    if (str.startsWith("\"") && str.endsWith("\""))
    {
        str = str.remove(0, 1);
        str = str.remove(str.length()-1, 1);
    }

    return str;
}

