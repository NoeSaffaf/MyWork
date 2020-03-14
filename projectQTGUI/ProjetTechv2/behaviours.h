#ifndef BEHAVIOURS_H
#define BEHAVIOURS_H
#include <iostream>
#include <QString>


class Behaviours
{
public:
    Behaviours();
    Behaviours(QString nomMat, QString group);
    QString getnomMat();
    QString getnomGroup();
private:
    QString m_nomMat;
    QString m_group;
};

#endif // BEHAVIOURS_H
