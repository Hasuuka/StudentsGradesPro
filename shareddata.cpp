#include "shareddata.h"

SharedData::SharedData()
{

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
