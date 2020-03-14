#include "materiauxajoutes.h"


//Classe pour instancier des objets de type Mat

MateriauxAjoutes::MateriauxAjoutes(): m_typemat(-1),m_nom("DefaultMat"),m_ELouPLA(-1),m_ISOouCub(-1),m_Eyoung(-1),m_Nu(-1),m_C11(-1),m_C12(-1),m_C44(-1),m_Zeta(-1),m_Lambda(-1),m_Gamma(-1)
{}

MateriauxAjoutes::MateriauxAjoutes(int typemat, QString nom, int ELouPLA, int ISOouCub, double Eyoung, double Nu):m_typemat(typemat), m_nom(nom),m_ELouPLA(ELouPLA),m_ISOouCub(ISOouCub),m_Eyoung(Eyoung),m_Nu(Nu),m_C11(-1),m_C12(-1),m_C44(-1),m_Zeta(-1),m_Lambda(-1),m_Gamma(-1)
{}

MateriauxAjoutes::MateriauxAjoutes(int typemat, QString nom, int ELouPLA, int ISOouCub, double C11, double C12, double C44):m_typemat(typemat),m_nom(nom),m_ELouPLA(ELouPLA),m_ISOouCub(ISOouCub),m_Eyoung(-1),m_Nu(-1),m_C11(C11),m_C12(C12),m_C44(C44),m_Zeta(-1),m_Lambda(-1),m_Gamma(-1)
{}

MateriauxAjoutes::MateriauxAjoutes(int typemat, QString nom, int ELouPLA, double Zeta, double Lambda, double Gamma):m_typemat(typemat),m_nom(nom),m_ELouPLA(ELouPLA),m_ISOouCub(-1),m_Eyoung(-1),m_Nu(-1),m_C11(-1),m_C12(-1),m_C44(-1),m_Zeta(Zeta),m_Lambda(Lambda),m_Gamma(Gamma)
{}

int MateriauxAjoutes::Gettypemat()
{
    return m_typemat;
}

QString MateriauxAjoutes::GetNom()
{
    return m_nom;
}

int MateriauxAjoutes::GetELouPLA()
{
    return m_ELouPLA;
}

int MateriauxAjoutes::GetISOouCub()
{
    return m_ISOouCub;
}

double MateriauxAjoutes::GetEyoung()
{
    return m_Eyoung;
}

double MateriauxAjoutes::GetNu()
{
    return m_Nu;
}

double MateriauxAjoutes::GetC11()
{
    return m_C11;
}

double MateriauxAjoutes::GetC12()
{
    return m_C12;
}

double MateriauxAjoutes::GetC44()
{
    return m_C44;
}

double MateriauxAjoutes::GetZeta()
{
    return m_Zeta;
}

double MateriauxAjoutes::GetLambda()
{
    return m_Lambda;
}

double MateriauxAjoutes::GetGamma()
{
    return m_Gamma;
}
