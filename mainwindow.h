#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
  void checkCell(int row, int column) const;
  void checkAllCells() const;

private:
    QString m_strLeftFilePath;
    QString m_strRightFilePath;

    QTextCodec *m_pTextCodec;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
