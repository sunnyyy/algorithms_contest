import java.util.Scanner;
import java.util.ArrayList;

public class snowluck {

	public static String snow(int n, ArrayList<String> trees) {
		// initialize graph with "max" distances
		int[][] g = new int[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				g[i][j] = Integer.MAX_VALUE;
			}
		}
		// initialize graph marking which 
		boolean[][] b = new boolean[n][n];
		// fill graph with trees
		for (int i = 0; i < trees.size(); i++) {
			String[] a = trees.get(i).split("\\s+");
			int ri = Integer.parseInt(a[0]);
			int rd = Integer.parseInt(a[1]);
			int gi = Integer.parseInt(a[2]);
			int gd = Integer.parseInt(a[3]);
			g[ri-1][i] = rd;
			g[gi-1][i] = gd;
			b[ri-1][i] = false;
		}
		// search min distances
		String result = "";
		boolean end = 0;
		for (int i = 0; i < n; i++) {
			// find min of row
			int min = Integer.MAX_VALUE;
			int minindex = 0;
			for (int j = 0; j < n; j++) {
				if (g[i][j] < min) {
					min = g[i][j];
					minindex = j;
				}
			}
			if (!b[i][minindex]) {
				result += "x ";
			} else {
				result += g[i][minindex]+" ";
			}
		}
		return result.substring(0, result.length()-1);
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = 0;
		ArrayList<String> trees = new ArrayList<String>();
		boolean firstline = True;
		while (scan.hasNextLine()) {
			String line = scan.nextLine();
			if (line.substring(0,2).equals("--")) {
				System.out.println(line);
				if (!firstline) {
					System.out.println(snow(n,trees));
					trees.clear();
				}
			} else if (line.length() == 1) {
				n = Integer.parseInt(line);
			} else {
				trees.add(line);
			}
		}
		System.out.println(snow(n,trees));
	}

}