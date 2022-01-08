#ifndef CSV_H
#define CSV_H
#include "QString"


class Csv
{
public:
    Csv(QString filename, QString filesize, QString students, QString bestGrades);

    const QString &filename() const;
    void setFilename(const QString &newFilename);

    const QString &filesize() const;
    void setFilesize(const QString &newFilesize);

    const QString &students() const;
    void setStudents(const QString &newStudents);

    const QString &bestGrades() const;
    void setBestGrades(const QString &newBestGrades);

private:
    QString m_filename;
    QString m_filesize;
    QString m_students;
    QString m_bestGrades;
};

#endif // CSV_H
