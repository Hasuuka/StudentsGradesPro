#ifndef STUDENTS_H
#define STUDENTS_H
#include <string>
#include <iostream>
using namespace std;



class students
{
public:
    students(string name, float math, float english, float progra1, float progra2, float statistics);
    void printInfo(){
        cout << m_name << m_math << m_english << m_progra1 << m_progra2 << m_statistics << endl;
    }
private:
    string m_name;
    float m_math;
    float m_english;
    float m_progra1;
    float m_progra2;
    float m_statistics;

};

#endif // STUDENTS_H
