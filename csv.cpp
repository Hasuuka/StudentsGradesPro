#include "csv.h"

Csv::Csv(QString filename, QString filesize, QString students, QString bestGrades)
{
    m_filename = filename;
    m_filesize = filesize;
    m_students = students;
    m_bestGrades = bestGrades;
}

const QString &Csv::filename() const
{
    return m_filename;
}

void Csv::setFilename(const QString &newFilename)
{
    m_filename = newFilename;
}

const QString &Csv::filesize() const
{
    return m_filesize;
}

void Csv::setFilesize(const QString &newFilesize)
{
    m_filesize = newFilesize;
}

const QString &Csv::students() const
{
    return m_students;
}

void Csv::setStudents(const QString &newStudents)
{
    m_students = newStudents;
}

const QString &Csv::bestGrades() const
{
    return m_bestGrades;
}

void Csv::setBestGrades(const QString &newBestGrades)
{
    m_bestGrades = newBestGrades;
}
