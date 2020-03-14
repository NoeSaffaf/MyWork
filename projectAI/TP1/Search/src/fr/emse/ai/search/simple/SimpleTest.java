package fr.emse.ai.search.simple;

import fr.emse.ai.search.solver.BreadthFirstTreeSearch;
import fr.emse.ai.search.solver.DepthFirstTreeSearch;

public class SimpleTest {

    public static void main(String[] args) {
        SimpleOrientedGraphProblem p1 = new SimpleOrientedGraphProblem();
        System.out.println("Solution to problem using depth first : ");
        System.out.println(new DepthFirstTreeSearch().solve(p1).pathToString());

        SimpleOrientedGraphProblem p2 = new SimpleOrientedGraphProblem();
        System.out.println("Solution to problem using breadth first : ");
        System.out.println(new BreadthFirstTreeSearch().solve(p2).pathToString());

        SimpleNotOrientedGraphProblem p3 = new SimpleNotOrientedGraphProblem();
        System.out.println("Solution to problem using depth first (not oriented) : ");
        System.out.println(new DepthFirstTreeSearch().solve(p3).pathToString());

        SimpleNotOrientedGraphProblem p4 = new SimpleNotOrientedGraphProblem();
        System.out.println("Solution to problem using breadth first (not oriented) : ");
        System.out.println(new BreadthFirstTreeSearch().solve(p4).pathToString());

        FarmerGraph p5 = new FarmerGraph();
        System.out.println("Solution to farmer problem using depth first (not oriented) : ");
        System.out.println(new DepthFirstTreeSearch().solve(p5).pathToString());

        MissionaryGraph p6 = new MissionaryGraph();
        System.out.println("Solution to missionary problem using depth first (not oriented) : ");
        System.out.println(new DepthFirstTreeSearch().solve(p6).pathToString());
    }
}
