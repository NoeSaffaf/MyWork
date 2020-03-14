#include "voxelgroups.h"

Voxelgroups::Voxelgroups(): m_nomMat("SansNomMat"),m_group("SansNomGroup")
{}

Voxelgroups::Voxelgroups(QString nomMat, QString group): m_nomMat(nomMat),m_group(group)
{}

QString Voxelgroups::getnomMat(){
    return m_nomMat;
}

QString Voxelgroups::getnomGroup(){
    return m_group;
}
