#include "csvdata.h"

#include <QRegExp>

#include <QDebug>

CsvData::CsvData(QString csvData)
{
    parse(csvData);
    normalize();
}

int CsvData::columnCount() {
    int columnCount=0;
    QStringList list;
    for (int i=0; i<rowCount(); ++i) {
        list = this->at(i);
        columnCount = qMax(list.count(), columnCount);
    }

    return columnCount;
}

void CsvData::parse(QString in) {
    static QRegExp anyLineEndings("\r\n|\r|\n");
    QStringList rows = in.split(anyLineEndings, QString::KeepEmptyParts);

    foreach(QString row, rows)
    {
        if (!row.isEmpty()) {
            append(row.split(';', QString::KeepEmptyParts));
        }
    }
}


void CsvData::appendRows(int numRows) {
    QStringList emptyRow;
    for (int j=0; j<columnCount(); ++j)
    {
        emptyRow.append("");
    }
    for (int i=0; i<numRows; ++i) {
        this->append(emptyRow);
    }
}


void CsvData::appendColumns(int numColumns) {
    for(int i=0; i<rowCount(); ++i) {
        for (int j=0; j<numColumns; ++j) {
            QStringList list = at(i);
            list.append("");
        }
    }

}

void CsvData::extendRows(int numTotRows) {
    Q_ASSERT(numTotRows > 0);
    appendRows(numTotRows - rowCount());
}


void CsvData::extendColumns(int numTotColumns) {
    Q_ASSERT(numTotColumns > 0);
    appendColumns(numTotColumns - columnCount());
}

void CsvData::normalize() {
    int nColumnCount = columnCount();

    for(int i=0; i< rowCount(); ++i) {
        extendRows(nColumnCount);
    }
}
