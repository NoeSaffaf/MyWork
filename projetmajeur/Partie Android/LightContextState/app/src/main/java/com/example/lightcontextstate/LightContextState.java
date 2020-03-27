package com.example.lightcontextstate;

/*La classe décrit l'état d'une lampe*/

public class LightContextState {
    private long id;

    private String status;

    private int bri;

    private int colour;

    private int sat;


    static String ON="ON";
    static String OFF="OFF";

    public LightContextState(Long id, String status, int bri,int colour, int sat){
        this.id=id;
        this.status=status;
        this.bri=bri;
        this.colour=colour;
        this.sat=sat;
    }

    public long getId() {
        return id;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status){this.status=status;}

    public int getBri(){return bri;}

    public void setBri(int bri){this.bri=bri;}

    public int getColour(){return colour;}

    public void setColour(int colour){this.colour=colour;}

    public int getSat(){return sat;}

    public void setSat(int sat){this.sat=sat;}

}
