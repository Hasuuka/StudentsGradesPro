#include "csvlistmodel.h"

CsvListModel::CsvListModel(QList<Csv>* csvs, QObject *parent)
    : QAbstractItemModel(parent), m_csvs(csvs)
{

}

QVariant CsvListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Filename";
            case 1: return "FileSize";
            case 2: return "Students";
            case 3: return "Best grades";
            }
        } else{
            return QString::number(section + 1);
        }
    }
     return QVariant();
}

QModelIndex CsvListModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex CsvListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int CsvListModel::rowCount(const QModelIndex &parent) const
{
    return m_csvs->size();
}

int CsvListModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant CsvListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
if(role == Qt::DisplayRole){
    const Csv& csv = m_csvs->at(index.row());
    switch(index.column()){
        case 0: return csv.filename();
        case 1: return  csv.filesize();
        case 2: return csv.students();
        case 3: return csv.bestGrades();
    }
}
    // FIXME: Implement me!
    return QVariant();
}
