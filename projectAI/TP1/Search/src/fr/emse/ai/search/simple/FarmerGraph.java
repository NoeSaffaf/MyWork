package fr.emse.ai.search.simple;

import fr.emse.ai.search.core.Problem;

import java.util.ArrayList;
import java.util.Collection;

public class FarmerGraph implements Problem {

    FarmerProblem initialState = new FarmerProblem(FarmerProblem.GWC);
    FarmerProblem finalState = new FarmerProblem(FarmerProblem.H2);

    @Override
    public Object getInitialState() {
        return initialState;
    }

    @Override
    public boolean isGoal(Object state) {
        return state.equals(finalState);
    }

    @Override
    public Collection<Object> getActions(Object state) {
        ArrayList<Object> actions = new ArrayList<Object>();
        String s = ((FarmerProblem) state).value;
        if (s.equals(FarmerProblem.GWC)) {
            actions.add("go to WC2");
        } else if (s.equals(FarmerProblem.GW)) {
            actions.add("go to G2");
            actions.add("go to W2");
        } else if (s.equals(FarmerProblem.WC)) {
            actions.add("go to W2");
            actions.add("go to C2");
            actions.add("go to WC2");
        } else if (s.equals(FarmerProblem.GC)) {
            actions.add("go to C2");
            actions.add("go to G2");
        } else if (s.equals(FarmerProblem.G)) {
            actions.add("go to G2");
            actions.add("go to H2");
        } else if (s.equals(FarmerProblem.W2)) {
            actions.add("go to GW");
            actions.add("go to WC");
        } else if (s.equals(FarmerProblem.G2)) {
            actions.add("go to G");
            actions.add("go to GW");
            actions.add("go to GC");
        } else if (s.equals(FarmerProblem.C2)) {
            actions.add("go to WC");
            actions.add("go to GC");
        } else if (s.equals(FarmerProblem.WC2)) {
            actions.add("go to WC");
            actions.add("go to GWC");
        } else if (s.equals(FarmerProblem.H2)) {

        }
        return actions;
    }

    @Override
    public Object getNextState(Object state, Object action) {
        if (action.equals("go to GWC")) return new FarmerProblem(FarmerProblem.GWC);
        if (action.equals("go to GW")) return new FarmerProblem(FarmerProblem.GW);
        if (action.equals("go to GC")) return new FarmerProblem(FarmerProblem.GC);
        if (action.equals("go to WC")) return new FarmerProblem(FarmerProblem.WC);
        if (action.equals("go to G")) return new FarmerProblem(FarmerProblem.G);
        if (action.equals("go to W")) return new FarmerProblem(FarmerProblem.W);
        if (action.equals("go to C")) return new FarmerProblem(FarmerProblem.C);
        if (action.equals("go to H")) return new FarmerProblem(FarmerProblem.H);
        if (action.equals("go to GWC2")) return new FarmerProblem(FarmerProblem.GWC2);
        if (action.equals("go to GW2")) return new FarmerProblem(FarmerProblem.GW2);
        if (action.equals("go to GC2")) return new FarmerProblem(FarmerProblem.GC2);
        if (action.equals("go to WC2")) return new FarmerProblem(FarmerProblem.WC2);
        if (action.equals("go to G2")) return new FarmerProblem(FarmerProblem.G2);
        if (action.equals("go to W2")) return new FarmerProblem(FarmerProblem.W2);
        if (action.equals("go to C2")) return new FarmerProblem(FarmerProblem.C2);
        if (action.equals("go to H2")) return new FarmerProblem(FarmerProblem.H2);
        return null;
    }

    @Override
    public double getStepCost(Object start, Object action, Object dest) {
        return 1;
    }
}
