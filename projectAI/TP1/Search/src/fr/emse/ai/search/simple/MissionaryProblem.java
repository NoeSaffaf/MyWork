package fr.emse.ai.search.simple;

public class MissionaryProblem {

    //M représente un missionaire, C un cannibal SUR LA BORD DE DEPART 1
    //La présence de 2 signifie que le bateau se situe sur le bord d'arrivée de la rive, sinon, elle est dans le bord de depart
    //exemple: MMMCC signifie que sur le coté 1(départ) on trouve 3 missionaires et 2 cannibales et le bateau, sur le coté 2, 1 cannibale
    //Autre Exemple: MMC2 signifie que il y a 2 missionaires et 1 cannibale coté 1, et 2 cannibales et 1 missionaire coté 2 avec le bateau,
    //cette situation est interdite

    public final static String MMMCCC = "MMMCCC"; //depart
    public final static String MMMCC = "MMMCC";
    public final static String MMMC = "MMMC";
    public final static String MMM = "MMM";

    public final static String MMCCC = "MMCCC"; //impossible
    public final static String MMCC = "MMCC";
    public final static String MMC = "MMC"; //impossible
    public final static String MM = "MMC"; //impossible

    public final static String MCCC = "MCCC"; //impossible
    public final static String MCC = "MCC"; //impossible
    public final static String MC = "MC";
    public final static String M = "M"; //impossible

    public final static String CCC = "CCC";
    public final static String CC = "CC";
    public final static String C = "C";
    public final static String H = "H";//impossible (le bateau est tout seul)

    public final static String MMMCCC2 = "MMMCCC2"; //impossible (le bateau est tout seul)
    public final static String MMMCC2 = "MMMCC2";
    public final static String MMMC2 = "MMMC2";
    public final static String MMM2 = "MMM2";

    public final static String MMCCC2 = "MMCCC2"; //impossible
    public final static String MMCC2 = "MMCC2";
    public final static String MMC2 = "MMC2"; //impossible
    public final static String MM2 = "MM2"; //impossible

    public final static String MCCC2 = "MCCC2"; //impossible
    public final static String MCC2 = "MCC2"; //impossible
    public final static String MC2 = "MC2";
    public final static String M2 = "M2"; //impossible

    public final static String CCC2 = "CCC2";
    public final static String CC2 = "CC2";
    public final static String C2 = "C2";
    public final static String H2 = "H2"; //objectif

    public String value;

    public MissionaryProblem(String value) {
        this.value = value;
    }

    public boolean equals(Object o) {
        if (o instanceof MissionaryProblem) {
            return ((MissionaryProblem) o).value.equals(this.value);
        }
        return false;
    }

    public String toString() {
        return value;
    }
}
