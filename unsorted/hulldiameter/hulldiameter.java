import java.util.*;
import java.io.*;

public class hulldiameter {

    public static void answer(ArrayList<Double> xs, ArrayList<Double> ys) {
	double max_dist = 0;
	int i = -1;
	int j = -1;
	for (int k = 0; k < xs.size()-1; k++) {
	    for (int l = k; l < xs.size(); l++) {
		double dx = xs.get(l) - xs.get(k);
		double dy = ys.get(l) - ys.get(k);
		double dist = Math.sqrt(dx*dx + dy*dy);
		if (dist > max_dist) {
		    max_dist = dist;
		    i = k;
		    j = l;
		}
	    }
	}
	System.out.println(max_dist + " " + i + " " + j);
    }

    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	ArrayList<Double> xs = new ArrayList<>();
	ArrayList<Double> ys = new ArrayList<>();
	//int i = -1;
	//int j = -1;
	while (scan.hasNextLine()) {
	    String s = scan.nextLine();
	    if (s.substring(0,2).equals("--")) {
		System.out.println(s);
		
	    } else {
		String[] a = s.split("\\s+");
		if (a.length==1) {
		    for (int li = 0; li < Integer.parseInt(a[0]); li++) {
			xs.add(Integer.parseInt(a[0]));
			ys.add(Integer.parseInt(a[1]));
		    }
		}
	    }
	}
    }

}
