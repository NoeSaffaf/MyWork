#ifndef VOXELGROUPS_H
#define VOXELGROUPS_H
#include <iostream>
#include <QString>


class Voxelgroups
{
public:
    Voxelgroups();
    Voxelgroups(QString nomMat, QString group);
    QString getnomMat();
    QString getnomGroup();

private:
    QString m_nomMat;
    QString m_group;
};

#endif // VOXELGROUPS_H
