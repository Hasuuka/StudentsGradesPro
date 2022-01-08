#include "shareddata.h"

SharedData::SharedData()
{
    m_csvs.append(Csv("test", "2.0", "idk", "1.0"));

}

SharedData* SharedData::instance(){
    static SharedData* model = new SharedData();
    return model;
}

QList<Csv>* SharedData::csvs(){
    return &m_csvs;
}

void SharedData::addCsv(QString filename, QString filesize, QString students, QString bestGrades){
    m_csvs.append(Csv(filename, filesize, students, bestGrades));
}
