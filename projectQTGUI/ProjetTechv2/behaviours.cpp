#include "behaviours.h"


Behaviours::Behaviours(): m_nomMat("SansNomMat"),m_group("SansNomGroup")
{}

Behaviours::Behaviours(QString nomMat, QString group): m_nomMat(nomMat),m_group(group)
{}

QString Behaviours::getnomMat(){
    return m_nomMat;
}

QString Behaviours::getnomGroup(){
    return m_group;
}
