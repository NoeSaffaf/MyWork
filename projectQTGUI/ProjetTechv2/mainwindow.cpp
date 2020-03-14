#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QList>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "materiauxajoutes.h"
#include "voxelgroups.h"
#include "behaviours.h"

//Constructeur avec l'ajout de quelques connexions
MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->comboBoxPrincipale, SIGNAL(activated(int)), this, SLOT(ChoixEnabled(int)));
    connect(ui->ButtomAddMateriau, SIGNAL(clicked()), this, SLOT(AjouterMateriau()));
    connect(ui->ButtomSuppMateriau, SIGNAL(clicked()), this, SLOT(SupprimerMateriau()));
    connect(ui->ButtomAddVsetProp, SIGNAL(clicked()), this, SLOT(AjouterVset()));
    connect(ui->ButtomSupprimerVsetProp, SIGNAL(clicked()), this, SLOT(SupprimerVset()));
    connect(ui->ButtomEcrireFichier, SIGNAL(clicked()), this, SLOT(EcrireFichier()));
    connect(ui->ButtonChoisirAdresse, SIGNAL(clicked()), this, SLOT(ChercherpathFile()));
    connect(ui->ButtonSaveFile, SIGNAL(clicked()), this, SLOT(SauvegarderFile()));
}


//Permet de Enable ou disable les options selon le mode choisis
void MainWindow::ChoixEnabled(int A)
{
    if (A==0){
        ui->GroupBoxMat->setEnabled(false);
        ui->GroupBoxVoxels->setEnabled(false);
        ui->groupBoxProblemeMat->setEnabled(false);
        ui->groupBoxPhasefield->setEnabled(false);
        ui->GroupBoxVsets_type->setEnabled(false);
        ui->GroupBoxOutput->setEnabled(false);
        ui->GroupBoxThreading->setEnabled(false);
        ui->groupBoxGeometryFile->setEnabled(false);
        ui->GroupBoxZeroMQ->setEnabled(false);
        ui->groupBoxConditionIni->setEnabled(false);
        ui->GroupBoxSolver->setEnabled(false);
    }
    else {
        ui->groupBoxGeometryFile->setEnabled(true);
        ui->GroupBoxThreading->setEnabled(true);
        ui->GroupBoxZeroMQ->setEnabled(true);
        ui->groupBoxConditionIni->setEnabled(true);
        ui->GroupBoxSolver->setEnabled(true);
    }


    if (A==1){
        ui->GroupBoxMat->setEnabled(true);
        ui->GroupBoxVoxels->setEnabled(true);
        ui->TypeVoxel->setDisabled(true);
        ui->TypeVoxel->setText("Mechanical");
        ui->TypeBehaviour->setText("Elasticity");
        ui->groupBoxProblemeMat->setEnabled(true);
        ui->GroupBoxVsets_type->setEnabled(true);
        ui->GroupBoxOutput->setEnabled(true);
        }

    if (A==2){
        ui->GroupBoxVoxels->setEnabled(true);
        ui->TypeVoxel->setDisabled(true);
        ui->TypeVoxel->setText("Phase Field");
        ui->TypeBehaviour->setDisabled(true);
        ui->TypeBehaviour->setText("cohn_hillard");
        ui->groupBoxPhasefield->setEnabled(true);
        ui->GroupBoxVsets_type->setEnabled(true);
        ui->GroupBoxMat->setEnabled(true);
        ui->groupBoxProblemeMat->setEnabled(false);
        ui->GroupBoxOutput->setEnabled(true);
        ui->groupBoxSymouISO->setDisabled(true);
        ui->groupBoxPropMatPhase->setEnabled(true);
        ui->GroupBoxC11C12C44->setEnabled(false);
        ui->GroupBoxEouNu->setEnabled(false);
        }

    else {
        ui->groupBoxPhasefield->setEnabled(false);
        ui->groupBoxSymouISO->setEnabled(true);
        ui->groupBoxPropMatPhase->setEnabled(false);
    }

    if (A==3){
        ui->GroupBoxMat->setEnabled(true);
        ui->GroupBoxVoxels->setEnabled(true);
        ui->TypeVoxel->setDisabled(true);
        ui->TypeVoxel->setText("Mechanical_Linear_PolyOpti_C");
        ui->groupBoxProblemeMat->setEnabled(true);
        ui->GroupBoxVsets_type->setEnabled(true);
        ui->GroupBoxOutput->setEnabled(true);
    }

}



//Fonction Pour ajouter un Materiau
void MainWindow::AjouterMateriau(){

    int n_typemat=-1;
    double n_Eyoung=-1;
    int n_ELouPLA=-1;
    int n_ISOouCub=-1;
    double n_Nu=-1;
    double n_C11=-1;
    double n_C12=-1;
    double n_C44=-1;
    double n_zeta=-1;
    double n_lambda=-1;
    double n_gamma=-1;

    n_typemat=ui->comboBoxPrincipale->currentIndex();

    QString nom=ui->lineEditNameMat->text();

    QString nomMat=ui->lineEditNameMat->text();
    ui->comboBoxMatassocie->addItem(nom);


    if (ui->RadioElastique->isChecked()){
        nomMat.append(" elasticity");
        n_ELouPLA=1;
    }

    if (ui->RadioPlastique->isChecked()){
        nomMat.append(" plasticity");
        n_ELouPLA=2;
    }

    if (ui->RadioCahn_hillard->isChecked()){
        nomMat.append(" Cahn_hillard");
        n_ELouPLA=3;
    }

    if (n_typemat==1 || n_typemat==3){


        if (ui->RadioIsotopique->isChecked()){
            nomMat.append(" isotropic E=");
            nomMat.append(QString:: number(ui->spinboxE->value()));
            nomMat.append(" nu=");
            nomMat.append(QString:: number(ui->spinBoxNu->value()));
            n_ISOouCub=1;
            n_Eyoung=ui->spinboxE->value();
            n_Nu=ui->spinBoxNu->value();


        }

        if (ui->RadioCubique->isChecked()){
            nomMat.append(" cubic C11=");
            nomMat.append(QString:: number(ui->spinBoxC11->value()));
            nomMat.append(" C12=");
            nomMat.append(QString:: number(ui->spinBoxC12->value()));
            nomMat.append(" C44=");
            nomMat.append(QString:: number(ui->spinBoxC44->value()));
            n_ISOouCub=2;
            n_C11=ui->spinBoxC11->value();
            n_C12=ui->spinBoxC12->value();
            n_C44=ui->spinBoxC44->value();
        }

        if (nomMat.isEmpty()){
            ui->textEditMatList->append("Supprimer cette ligne svp");
        }
        else {
            ui->textEditMatList->append(nomMat);
        }

        //ajouter l'objet materiaux dans la liste
        if (n_ISOouCub==1){
            MateriauxAjoutes *monObjet = new MateriauxAjoutes(n_typemat,nom,n_ELouPLA,n_ISOouCub,n_Eyoung,n_Nu);
            listeobjet.append(monObjet);
        }
        if (n_ISOouCub==2){
            MateriauxAjoutes *monObjet = new MateriauxAjoutes(n_typemat,nom,n_ELouPLA,n_ISOouCub,n_C11,n_C12,n_C44);
            listeobjet.append(monObjet);
        }
    }

    if (n_typemat==2){

        nomMat.append(" Zeta=");
        nomMat.append(QString:: number(ui->spinBoxZeta->value()));
        nomMat.append(" Lambda=");
        nomMat.append(QString:: number(ui->spinBoxLambda->value()));
        nomMat.append(" Gamma=");
        nomMat.append(QString:: number(ui->spinBoxGamma->value()));
        n_lambda=ui->spinBoxLambda->value();
        n_zeta=ui->spinBoxZeta->value();
        n_gamma=ui->spinBoxGamma->value();

        if (nomMat.isEmpty()){
            ui->textEditMatList->append("Supprimer cette ligne svp");
        }
        else {
            ui->textEditMatList->append(nomMat);
        }

        //ajouter l'objet materiaux dans la liste
        MateriauxAjoutes *monObjet = new MateriauxAjoutes(n_typemat,nom,n_ELouPLA,n_zeta,n_lambda,n_gamma);
        listeobjet.append(monObjet);
    }
}



void MainWindow::SupprimerMateriau(){
    if (listeobjet.size()!=0){
        listeobjet.removeFirst();
    }
}

void MainWindow::SupprimerVset(){
    if (listevoxel.size()!=0){
        listevoxel.removeFirst();
    }
    if (listebehaviours.size()!=0){
        listebehaviours.removeFirst();
    }
}

void MainWindow::AjouterVset(){
    QString nom=ui->lineEditNameGroup->text();
    nom.append(" ");
    nom.append(ui->comboBoxMatassocie->currentText());
    ui->textEditVset->append(nom);

    Voxelgroups* monGroupe=new Voxelgroups(ui->comboBoxMatassocie->currentText(),ui->lineEditNameGroup->text());
    listevoxel.append(monGroupe);
    Behaviours* bgroup=new Behaviours(ui->comboBoxMatassocie->currentText(),ui->lineEditNameGroup->text());
    listebehaviours.append(bgroup);
}



// Permet d'ecrire un buffer avec les entree de la fenetre et la liste d'objet créé (cette partie
// est en commentaire car elle ne fonctionne pas

QString MainWindow::EcrireFichier(){

    QString buffer;

    buffer="";

    //buffer problem;
    buffer.append("problem ");

    int IndexPrin=ui->comboBoxPrincipale->currentIndex();

    if (IndexPrin == 1){
        buffer.append("Mechanical {\n");
    }
    else if (IndexPrin == 2){
        buffer.append("Phase Field {\n");
    }
    else if (IndexPrin == 3){
        buffer.append("Mechanical_Linear_PolyOpti_C {\n");
        }
    else{
       return buffer;
    }

    if (IndexPrin == 1 || IndexPrin == 3) {

        buffer.append("    tolerance_delta_epsilon ");
        buffer.append(QString:: number(ui->spinBoxDeltaEpsilon->value()));
        buffer.append("\n");
        buffer.append("    tolerance_equilibrium ");
        buffer.append(QString:: number(ui->spinboxEquilibre->value()));
        buffer.append("\n");
        buffer.append("    reference_stiffness {\n");


        if (ui->RadioIsotopiqueProbleme->isChecked()){
            buffer.append("        sym isotropic {\n");
            buffer.append("            E ");
            buffer.append(QString:: number(ui->spinboxEProbleme->value()));
            buffer.append(".\n");
            buffer.append("            nu ");
            buffer.append(QString:: number(ui->spinBoxNuProbleme->value()));
            buffer.append("\n");
        }

        if (ui->RadioCubiqueProbleme->isChecked()){
            buffer.append("        sym cubic {\n");
            buffer.append("            C11 ");
            buffer.append(QString:: number(ui->spinBoxC11Probleme->value()));
            buffer.append("\n");
            buffer.append("            C12 ");
            buffer.append(QString:: number(ui->spinBoxC12Probleme->value()));
            buffer.append("\n");
            buffer.append("            C12 ");
            buffer.append(QString:: number(ui->spinBoxC44Probleme->value()));
            buffer.append("\n");
        }

        buffer.append("        }\n");
        buffer.append("    }\n");
    }

    if (IndexPrin == 2) {
        buffer.append("        max_time_steps ");
        buffer.append(QString:: number(ui->spinboxMaxtimesteps->value()));
        buffer.append("\n");
        buffer.append("        max_time ");
        buffer.append(QString:: number(ui->spinboxMaxtime->value()));
        buffer.append("\n");
        buffer.append("        dt ");
        buffer.append(QString:: number(ui->spinBoxdt->value()));
        buffer.append("\n");
        buffer.append("        save_every_x_steps ");
        buffer.append(QString:: number(ui->spinboxS_EverStep->value()));
        buffer.append("\n");
    }

    buffer.append("}\n");
    buffer.append("\n");

    //Buffer Ajouter Algoritm

    if (ui->TextEditAlgorithm->text()!=""){
        buffer.append("algorithm ");
        buffer.append(ui->TextEditAlgorithm->text());
        buffer.append("\n\n");
    }

    //Buffer Ajouter materiau propriétés

    if (listeobjet.size() > 0 ){

        buffer.append("material_properties {\n");

        for (int i=0; i<listeobjet.size() ; i++){

            MateriauxAjoutes* monObjet=listeobjet.at(i);

            buffer.append("    ");
            buffer.append(monObjet->GetNom());

            if (monObjet->GetELouPLA()==1){
                buffer.append(" elasticity {\n");
            }
            if (monObjet->GetELouPLA()==2){
                buffer.append(" plasticity {\n");
            }
            if (monObjet->GetELouPLA()==3){
                buffer.append(" cahn_hillard {\n");
            }

            if (IndexPrin==1 || IndexPrin==3){

                buffer.append("        stiffness {\n");

                if (monObjet->GetISOouCub()==1){
                    buffer.append("            sym isotropic\n");
                    buffer.append("            E ");
                    buffer.append(QString:: number(monObjet->GetEyoung()));
                    buffer.append(".\n");
                    buffer.append("            nu ");
                    buffer.append(QString:: number(monObjet->GetNu()));
                    buffer.append("\n");
                }
                if (monObjet->GetISOouCub()==2){
                    buffer.append("            sym cubic\n");
                    buffer.append("            C11 ");
                    buffer.append(QString:: number(monObjet->GetC11()));
                    buffer.append("\n");
                    buffer.append("            C12 ");
                    buffer.append(QString:: number(monObjet->GetC12()));
                    buffer.append("\n");
                    buffer.append("            C12 ");
                    buffer.append(QString:: number(monObjet->GetC44()));
                    buffer.append("\n");
                }
                buffer.append("        }\n");
            }

            if (IndexPrin==2){
                buffer.append("        zeta ");
                buffer.append(QString:: number(monObjet->Gettypemat()));
                buffer.append("\n");
                buffer.append("        lambda ");
                buffer.append(QString:: number(monObjet->GetLambda()));
                buffer.append("\n");
                buffer.append("        gamma ");
                buffer.append(QString:: number(monObjet->GetGamma()));
                buffer.append("\n");
            }

            buffer.append("    }\n");
        }
        buffer.append("}\n");
        buffer.append("\n");
    }


    //Buffer Ajouter Voxel

    buffer.append("voxels {\n");
    buffer.append("    type {\n");

    if (IndexPrin==1 || IndexPrin==3){
        buffer.append("        Mechanical ");
    }
    else if (IndexPrin==2){
        buffer.append("        Phase_Field ");
    }

    if (ui->radioButtonAll->isChecked()){
        buffer.append("\"ALL\"");
    }
    else if (ui->radioButtonEach->isChecked()){
        buffer.append("\"ALL\"");
    }

    else if(listevoxel.size()>0 && ui->radioButtonFairedesgroupes->isChecked()){
        buffer.append("\"");
        for (int i=0; i<listevoxel.size() ; i++){
            Voxelgroups* monVoxel=listevoxel.at(i);
            buffer.append(monVoxel->getnomGroup());
            if (i<listevoxel.size()-1){
                buffer.append(" ");
            }
        }
        buffer.append("\"");
    }
    buffer.append("\n");
    buffer.append("    }\n");
    buffer.append("    FFT_derivatives ");
    if (IndexPrin==1 || IndexPrin==3){
        buffer.append("Mechanical\n");
    }
    else if (IndexPrin==2){
        buffer.append("Phase_Field\n");
    }

    buffer.append("        Gamma rotated\n");
    buffer.append("        Equilibrium rotated\n");
    buffer.append("    }\n");
    buffer.append("    vsets_properties {\n");

    if (listevoxel.size() > 0 && ui->radioButtonFairedesgroupes->isChecked()){
        for (int i=0; i<listevoxel.size() ; i++){
            Voxelgroups* monVoxel=listevoxel.at(i);
            buffer.append("        ");
            buffer.append(monVoxel->getnomGroup());
            buffer.append(" ");
            buffer.append(monVoxel->getnomMat());
            buffer.append("\n");
        }
    }
    else if (ui->radioButtonAll->isChecked()){
        buffer.append("        ALL ");
        for (int i=0; i<listeobjet.size() ; i++){
            MateriauxAjoutes* monObjet=listeobjet.at(i);
            buffer.append(monObjet->GetNom());
            buffer.append(" ");
        }
    }

    else if (ui->radioButtonEach->isChecked()){
        buffer.append("        EACH ");
        for (int i=0; i<listeobjet.size() ; i++){
            MateriauxAjoutes* monObjet=listeobjet.at(i);
            buffer.append(monObjet->GetNom());
            buffer.append(" ");
        }
        buffer.append(" {\n");
        buffer.append("            rotation ori_euler\n");
        buffer.append("         }\n");
    }
    buffer.append("    }\n");
    buffer.append("}\n");
    buffer.append("\n");


    //Buffer Partie Behaviours

    buffer.append("behaviours {\n");
    if (IndexPrin==2){
        buffer.append("    cahn_hilliard {\n");
        buffer.append("        vsets ");
        if (ui->radioButtonAll->isChecked()){
            buffer.append("\"ALL\"");
        }
        else if(listebehaviours.size()>0 && ui->radioButtonFairedesgroupes->isChecked()){
            buffer.append("\"");
            for (int i=0; i<listebehaviours.size() ; i++){
                Behaviours* monBehaviour=listebehaviours.at(i);
                buffer.append(monBehaviour->getnomGroup());
                if (i<listevoxel.size()-1){
                    buffer.append(" ");
                }
            }
            buffer.append("\"");
        }
    }
    else if (IndexPrin==1){
        buffer.append("    elasticity {\n");
        buffer.append("        vsets ");
        if (ui->radioButtonAll->isChecked()){
            buffer.append("\"ALL\"");
        }
        else if(listebehaviours.size()>0 && ui->radioButtonFairedesgroupes->isChecked()){
            buffer.append("\"");
            for (int i=0; i<listebehaviours.size() ; i++){
                Behaviours* monBehaviour=listebehaviours.at(i);
                buffer.append(monBehaviour->getnomGroup());

                buffer.append(" ");
            }
            buffer.append("\"");
        }

    }
    buffer.append("\n");
    buffer.append("    }\n");
    buffer.append("}\n");
    buffer.append("\n");


    //buffer Partie solver

    if (ui->radioButtonCG->isChecked()){
        buffer.append("solver CG {\n");
        buffer.append("    max_iter ");
        buffer.append(QString::number(ui->spinBoxMax_iter->value()));
        buffer.append("\n");
        buffer.append("tolerance_residual ");
        buffer.append(QString::number(ui->spinBoxTolresidual->value()));
        buffer.append("\n}\n\n");
    }

    if (ui->radioButtonbiCGstab->isChecked()){
        buffer.append("solver CG {\n");
        buffer.append("    max_iter ");
        buffer.append(QString::number(ui->spinBoxMax_iter->value()));
        buffer.append("\n");
        buffer.append("tolerance_residual ");
        buffer.append(QString::number(ui->spinBoxTolresidual->value()));
        buffer.append("\n");
        buffer.append("    initial_solution_vector ");
        buffer.append(QString::number(ui->spinBoxSolVector->value()));
        buffer.append("\n}\n\n");
    }



    //buffer Partie Geometry file

    if (ui->radio1fichier->isChecked()){
        buffer.append("geometry r_file {\n");
        buffer.append("    file \"");
        buffer.append(ui->TextEditGeometryFile1->text());
        buffer.append("\"\n");
        buffer.append("}\n\n");
    }

    if (ui->radio2fichier->isChecked()){
        buffer.append("geometry tesr_file {\n");
        buffer.append("    file \"");
        buffer.append(ui->TextEditGeometryFile1->text());
        buffer.append("\"\n");
        buffer.append("    ori \"");
        buffer.append(ui->TextEditGeometryFile2->text());
        buffer.append("\"\n");
        buffer.append("}\n\n");
    }



    //Buffer Partie Threading

    buffer.append("threading {\n");
    buffer.append("    fftw ");
    buffer.append(QString::number(ui->spinBoxFftw->value()));
    buffer.append("\n");
    buffer.append("    voxels ");
    buffer.append(QString::number(ui->spinBoxVoxels->value()));
    buffer.append("\n");
    buffer.append("    unknowns ");
    buffer.append(QString::number(ui->spinBoxUnknowns->value()));
    buffer.append("\n");
    buffer.append("}\n");
    buffer.append("\n");

    //Buffer Partie Zero_mq
    if (ui->lineEditZeroMQ->text()!=""){
        buffer.append("zeromq {\n");
        buffer.append("    socket \"");
        buffer.append(ui->lineEditZeroMQ->text());
        buffer.append("\"\n}\n\n");
    }

    //Buffer Partie condition Limite

    if (ui->radioButtonSimple->isChecked()){
        buffer.append("applied_conditions mechanical_linear {\n");
        buffer.append("    E \"");
        buffer.append(QString::number(ui->SpinboxE1->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE2->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE3->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE4->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE5->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE6->value()));
        buffer.append("\"\n}\n\n");
    }

    if (ui->radioButtonDouble->isChecked()){
        buffer.append("applied_conditions mechanical_linear {\n");

        buffer.append("    mixed_BC \"");
        buffer.append(ui->lineEditMixedBC1->text());
        buffer.append(" ");
        buffer.append(ui->lineEditMixedBC2->text());
        buffer.append(" ");
        buffer.append(ui->lineEditMixedBC3->text());
        buffer.append(" ");
        buffer.append(ui->lineEditMixedBC4->text());
        buffer.append(" ");
        buffer.append(ui->lineEditMixedBC5->text());
        buffer.append(" ");
        buffer.append(ui->lineEditMixedBC6->text());
        buffer.append("\"\n");

        buffer.append("    E \"");
        buffer.append(QString::number(ui->SpinboxE1->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE2->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE3->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE4->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE5->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxE6->value()));
        buffer.append("\"\n");

        buffer.append("    S \"");
        buffer.append(QString::number(ui->SpinboxS1->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxS2->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxS3->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxS4->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxS5->value()));
        buffer.append(" ");
        buffer.append(QString::number(ui->SpinboxS6->value()));
        buffer.append("\"\n}\n\n");


    }

    if (ui->radioButtonImporter->isChecked()){
        buffer.append("initial_conditions  {\n");
        buffer.append("    defined_by_vtr_file \"");
        buffer.append(ui->lineEditFileImporter->text());
        buffer.append("\" {\n");
        buffer.append("        ");
        buffer.append(ui->lineEditOptionImporter->text());
        buffer.append("\n    }\n}\n\n");
    }

    //Buffer Partie output

    buffer.append("output {\n");
    buffer.append("    vtr {\n");
    buffer.append("        variables \"");
    buffer.append(ui->lineEditOutput->text());
    buffer.append("\"\n");
    buffer.append("    }\n");
    buffer.append("}\n");
    buffer.append("\n");

    ui->textEditOutput->append(buffer);
    return buffer;
}

void MainWindow::ChercherpathFile(){
    QFileDialog monFileDialog;
    ui->lineEditPathRimp->setText(monFileDialog.getExistingDirectory());
}

void MainWindow::SauvegarderFile(){
    QString bufferFinal=ui->textEditOutput->toPlainText();
    QString Path=ui->lineEditPathRimp->text();
    QString nomFichier=ui->lineEditnomFichierFinal->text();
    Path.append("/");
    Path.append(nomFichier);
    Path.append(".rinp");
    QFile monfile(Path);

    if(!monfile.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"title","Can't Open File");
    }
    QTextStream out(&monfile);
    out << bufferFinal;
    monfile.flush();
    monfile.close();

    if(monfile.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"title","Tout Roule comme sur des roulettes parallèles!");
    }
}





MainWindow::~MainWindow()
{
    delete ui;
}


