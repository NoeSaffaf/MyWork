#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "materiauxajoutes.h"
#include "voxelgroups.h"
#include "behaviours.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

    //Toutes les methodes de la fenetre

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ChoixEnabled(int);
    void AjouterMateriau();
    void SupprimerMateriau();
    void AjouterVset();
    void SupprimerVset();
    QString EcrireFichier();
    void ChercherpathFile();
    void SauvegarderFile();


private:
    Ui::MainWindow *ui;
    QList<MateriauxAjoutes*> listeobjet;
    QList<Voxelgroups*> listevoxel;
    QList<Behaviours*> listebehaviours;
};

#endif // MAINWINDOW_H
