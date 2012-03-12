#ifndef CSVDATA_H
#define CSVDATA_H

#include <QStringList>

class CsvData : public QList<QStringList>
{
public:
    CsvData(QString csvData);
    int rowCount() {return length();}
    int columnCount(void);

    void extendColumns(int numTotColumns);
    void extendRows(int numTotRows);
    void appendColumns(int numColumns);
    void appendRows(int numRows);

private:
    void parse(QString in);
    void normalize();

};

#endif // CSVDATA_H
