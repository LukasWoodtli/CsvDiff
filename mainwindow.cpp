#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QScrollBar>

#include <QDebug>

#include "openfilesdialog.h"
#include "csvdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QTextCodec::setCodecForCStrings(m_pTextCodec);

    connect(ui->m_pTableWidgetLeft->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->m_pTableWidgetRight->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->m_pTableWidgetLeft->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->m_pTableWidgetRight->horizontalScrollBar(), SLOT(setValue(int)));

    connect(ui->m_pTableWidgetRight->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->m_pTableWidgetLeft->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->m_pTableWidgetRight->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->m_pTableWidgetLeft->horizontalScrollBar(), SLOT(setValue(int)));

    QStringList arguments = QCoreApplication::arguments();


    if (arguments.length() == 3) {
        m_strLeftFilePath = arguments.at(1);
        m_strRightFilePath = arguments.at(2);
    }
    else {

        OpenFilesDialog fileDialog;

        int ret = fileDialog.exec();
        if (QDialog::Accepted == ret)
        {
            m_strLeftFilePath = fileDialog.getLeftFilePath();
            m_strRightFilePath = fileDialog.getRightFilePath();

        }
        else
        {
            qApp->exit();
        }
        }


    QFile file(m_strLeftFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
             qApp->exit(1);
    }

    QTextStream stream(&file);
    stream.setCodec("ISO 8859-15");

    QString text = stream.readAll();
    CsvData dataLeft(text);

    file.close();

    file.setFileName(m_strRightFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
             qApp->exit(1);
    }
    text = stream.readAll();
    CsvData dataRight(text);

    file.close();

    int nRows = qMax(dataLeft.rowCount(), dataRight.rowCount());
    int nColumns = qMax(dataLeft.columnCount(), dataRight.columnCount());

    dataLeft.extendRows(nRows);
    dataLeft.extendColumns(nColumns);

    dataRight.extendRows(nRows);
    dataRight.extendColumns(nColumns);

    Q_ASSERT(dataLeft.rowCount() == dataRight.rowCount());
    Q_ASSERT(dataLeft.columnCount() == dataRight.columnCount());

    ui->m_pTableWidgetLeft->setRowCount(dataLeft.rowCount());
    ui->m_pTableWidgetLeft->setColumnCount(dataLeft.columnCount());

    ui->m_pTableWidgetRight->setRowCount(dataRight.rowCount());
    ui->m_pTableWidgetRight->setColumnCount(dataRight.columnCount());

    for (int i=0; i<nRows; ++i)
    {
        for (int j=0; j<nColumns; ++j) {

            QTableWidgetItem* widgetItemLeft;
            QTableWidgetItem* widgetItemRight;

            widgetItemLeft  = new QTableWidgetItem(dataLeft.at(i).at(j));
            widgetItemRight = new QTableWidgetItem(dataRight.at(i).at(j));

            QColor background(Qt::darkYellow);
            if (dataLeft.at(i).at(j) != dataRight.at(i).at(j)) {

                widgetItemLeft->setBackgroundColor(background);
                widgetItemRight->setBackgroundColor(background);
            }

            ui->m_pTableWidgetLeft->setItem(i, j, widgetItemLeft);
            ui->m_pTableWidgetRight->setItem(i, j, widgetItemRight);

        }
    }

    connect(ui->m_pTableWidgetLeft, SIGNAL(cellChanged(int, int)), SLOT(checkCell(int, int)));
    connect(ui->m_pTableWidgetRight, SIGNAL(cellChanged(int, int)), SLOT(checkCell(int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkCell(int row, int column) const {
  Q_ASSERT(ui->m_pTableWidgetLeft->rowCount() > row);
  Q_ASSERT(ui->m_pTableWidgetLeft->columnCount() > column);

  QTableWidgetItem* itemLeft = ui->m_pTableWidgetLeft->item(row, column);
  Q_ASSERT(itemLeft);
  QString textLeft = itemLeft->text();
  
  Q_ASSERT(ui->m_pTableWidgetRight->rowCount() > row);
  Q_ASSERT(ui->m_pTableWidgetRight->columnCount() > column);
 
  QTableWidgetItem* itemRight = ui->m_pTableWidgetRight->item(row, column);
  Q_ASSERT(itemRight);
  QString textRight = itemRight->text();
  
  
  //QColor background(Qt::darkYellow);
  if (textLeft != textRight) {
    itemLeft->setData(Qt::BackgroundRole, QColor(Qt::darkYellow));
    itemRight->setData(Qt::BackgroundRole, QColor(Qt::darkYellow));

    //itemLeft->setBackground(Qt::darkYellow);
    //itemRight->setBackground(Qt::darkYellow);
  }
  

}


void MainWindow::checkAllCells() const {
Q_ASSERT(ui->m_pTableWidgetLeft->rowCount() == ui->m_pTableWidgetRight->rowCount());
Q_ASSERT(ui->m_pTableWidgetLeft->columnCount() == ui->m_pTableWidgetRight->columnCount());

    for (int i=0; i<ui->m_pTableWidgetLeft->rowCount(); ++i) {
        for (int j=0; j<ui->m_pTableWidgetLeft->columnCount(); ++j) {
            checkCell(i, j);
        }
    }
}
