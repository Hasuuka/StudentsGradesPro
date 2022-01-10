#include "students.h"



students::students(string name, float math, float english, float progra1, float progra2, float statistics)
{
    m_name = name;
    m_math = math;
    m_english = english;
    m_progra1 = progra1;
    m_progra2 = progra2;
    m_statistics = statistics;

    m_average = (m_math+m_english +m_progra1+ m_progra2+ m_statistics)/5;

}

float students::average() const
{
    return m_average;
}

const string &students::name() const
{
    return m_name;
}

