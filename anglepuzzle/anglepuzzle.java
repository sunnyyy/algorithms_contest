import java.util.Scanner;
import java.util.HashMap;
import java.util.ArrayList;
import java.awt.geom.Line2D;

public class anglepuzzle {

	public static void solve_angles(HashMap<String, Double> info, ArrayList<String> solve) {
		
		for (String angle: solve.iterator()) {

		}
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		// HashMap of angles we already have
		HashMap<String, Double> info = new HashMap<String, Double>();
		// ArrayList of angles to be solved;
		ArrayList<String> solve = new ArrayList<String>();
		while (scan.hasNextLine()) {
			String line = scan.nextLine();
			String[] sline = line.split("\\s+");
			if (sline[0].equals("--") {
				System.out.println(line);
			} else if (sline[0].equals(".") {
				solve_angles(info, solve);
				info.clear();
				solve.clear();
				System.out.println(line);
			} else if (sline[2].equals("?") {
				solve.add(sline[0])
			} else {
				System.out.println(line);
				info.put(sline[0], Double.parseDouble(sline[2]));
			}
		}
	}

}