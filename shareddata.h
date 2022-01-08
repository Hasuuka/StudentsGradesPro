#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include "csv.h"
#include "QList"
#include "QString"


class SharedData
{
private:
    SharedData();

public:
    QList<Csv>* csvs();
    static SharedData* instance();
    void addCsv(QString filename, QString filesize, QString students, QString bestGrades);



private:
    QList<Csv> m_csvs;
};

#endif // SHAREDDATA_H
