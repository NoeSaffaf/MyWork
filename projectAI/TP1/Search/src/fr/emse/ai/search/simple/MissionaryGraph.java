package fr.emse.ai.search.simple;

import fr.emse.ai.search.core.Problem;

import java.util.ArrayList;
import java.util.Collection;

public class MissionaryGraph implements Problem {

    MissionaryProblem initialState = new MissionaryProblem(MissionaryProblem.MMMCCC);
    MissionaryProblem finalState = new MissionaryProblem(MissionaryProblem.H2);

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
        String s = ((MissionaryProblem) state).value;
        if (s.equals(MissionaryProblem.MMMCCC)) {
            actions.add("go to MMMC2");
            actions.add("go to MMMCC2");
            actions.add("go to MMCC2");
        } else if (s.equals(MissionaryProblem.MMMCC)) {
            actions.add("go to MMM2");
            actions.add("go to MMCC2");
            actions.add("go to MMMC2");
        } else if (s.equals(MissionaryProblem.MMMC)) {
            actions.add("go to MMM2");
            actions.add("go to MC2");
        } else if (s.equals(MissionaryProblem.MMM)) {
        } else if (s.equals(MissionaryProblem.MMCC)) {
            actions.add("go to MC2");
            actions.add("go to CC2");
        } else if (s.equals(MissionaryProblem.MC)) {
            actions.add("go to H2");
            actions.add("go to C2");
        } else if (s.equals(MissionaryProblem.CCC)) {
            actions.add("go to CC2");
            actions.add("go to C2");
        } else if (s.equals(MissionaryProblem.CC)) {
            actions.add("go to H2");
            actions.add("go to C2");
        } else if (s.equals(MissionaryProblem.C)) {
            actions.add("go to H2");

        } else if (s.equals(MissionaryProblem.H2)) {
        } else if (s.equals(MissionaryProblem.MMMCC2)) {
            actions.add("go to MMMCCC");
        } else if (s.equals(MissionaryProblem.MMMC2)) {
            actions.add("go to MMMCCC");
            actions.add("go to MMMCC");
        } else if (s.equals(MissionaryProblem.MMM2)) {
            actions.add("go to MMMCC");
            actions.add("go to MMMC");
        } else if (s.equals(MissionaryProblem.MMCC2)) {
            actions.add("go to MMMCCC");
            actions.add("go to MMMCC");
        } else if (s.equals(MissionaryProblem.MC2)) {
            actions.add("go to MMCC");
            actions.add("go to MMMC");
        } else if (s.equals(MissionaryProblem.CCC2)) {
        } else if (s.equals(MissionaryProblem.CC2)) {
            actions.add("go to MMCC");
            actions.add("go to CCC");
        } else if (s.equals(MissionaryProblem.C2)) {
            actions.add("go to MC");
        }
        return actions;
    }

    @Override
    public Object getNextState(Object state, Object action) {
        if (action.equals("go to MMMCCC")) return new MissionaryProblem(MissionaryProblem.MMMCCC);
        if (action.equals("go to MMMCC")) return new MissionaryProblem(MissionaryProblem.MMMCC);
        if (action.equals("go to MMMC")) return new MissionaryProblem(MissionaryProblem.MMMC);
        if (action.equals("go to MMM")) return new MissionaryProblem(MissionaryProblem.MMM);
        if (action.equals("go to MMCC")) return new MissionaryProblem(MissionaryProblem.MMCC);
        if (action.equals("go to MC")) return new MissionaryProblem(MissionaryProblem.MC);
        if (action.equals("go to CCC")) return new MissionaryProblem(MissionaryProblem.CCC);
        if (action.equals("go to CC")) return new MissionaryProblem(MissionaryProblem.CC);
        if (action.equals("go to C")) return new MissionaryProblem(MissionaryProblem.C);

        if (action.equals("go to H2")) return new MissionaryProblem(MissionaryProblem.H2);
        if (action.equals("go to MMMCC2")) return new MissionaryProblem(MissionaryProblem.MMMCC2);
        if (action.equals("go to MMMC2")) return new MissionaryProblem(MissionaryProblem.MMMC2);
        if (action.equals("go to MMM2")) return new MissionaryProblem(MissionaryProblem.MMM2);
        if (action.equals("go to MMCC2")) return new MissionaryProblem(MissionaryProblem.MMCC2);
        if (action.equals("go to MC2")) return new MissionaryProblem(MissionaryProblem.MC2);
        if (action.equals("go to CCC2")) return new MissionaryProblem(MissionaryProblem.CCC2);
        if (action.equals("go to CC2")) return new MissionaryProblem(MissionaryProblem.CC2);
        if (action.equals("go to C2")) return new MissionaryProblem(MissionaryProblem.C2);
        return null;
    }

    @Override
    public double getStepCost(Object start, Object action, Object dest) {
        return 1;
    }
}
