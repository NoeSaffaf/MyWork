#ifndef MATERIAUXAJOUTES_H
#define MATERIAUXAJOUTES_H
#include <iostream>
#include <QString>

//classes pour les materiaux ajoutés avec differents constructeurs disponible et accesseurs

class MateriauxAjoutes
{
    public:
    MateriauxAjoutes();
    MateriauxAjoutes(int typemat, QString nom, int ELouPLA, int ISOouCub, double Eyoung, double Nu);
    MateriauxAjoutes(int typemat, QString nom, int ELouPLA, int ISOouCub, double C11, double C12, double C44);
    MateriauxAjoutes(int typemat, QString nom, int ELouPLA, double Zeta, double Lambda, double Gamma);
    int Gettypemat();
    int GetELouPLA();
    int GetISOouCub();
    double GetEyoung();
    double GetNu();
    double GetC11();
    double GetC12();
    double GetC44();
    double GetZeta();
    double GetLambda();
    double GetGamma();
    QString GetNom();


    private:
    int m_typemat;
    QString m_nom;
    int m_ELouPLA;
    int m_ISOouCub;
    double m_Eyoung;
    double m_Nu;
    double m_C11;
    double m_C12;
    double m_C44;
    double m_Zeta;
    double m_Lambda;
    double m_Gamma;
};

#endif // MATERIAUXAJOUTES_H
