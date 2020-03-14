package fr.emse.ai.search.simple;

public class FarmerProblem {
    public final static String GWC = "GWC";
    public final static String GW = "GW";
    public final static String GC = "GC";
    public final static String WC = "WC";
    public final static String G = "G";
    public final static String W = "W";
    public final static String C = "C";

    public final static String GWC2 = "GWC2";
    public final static String GW2 = "GW2";
    public final static String GC2 = "GC2";
    public final static String WC2 = "WC2";
    public final static String G2 = "G2";
    public final static String W2 = "W2";
    public final static String C2 = "C2";

    public final static String H = "H";
    public final static String H2 = "H2";


    public String value;

    public FarmerProblem(String value) {
        this.value = value;
    }

    public boolean equals(Object o) {
        if (o instanceof FarmerProblem) {
            return ((FarmerProblem) o).value.equals(this.value);
        }
        return false;
    }

    public String toString() {
        return value;
    }
}
