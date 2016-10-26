import java.util.Scanner;

public class turtledraw {

	public static void draw(String input) {
		char[][] a = new char[198][198];
		for (int col = 0; col < a.length; col++) {
			for (int row = 0; row < a[0].length; row++) {
				a[col][row] = ' ';
			}
		}
		int x = 99;
		int y = 99;
		int minx = 99;
		int miny = 99;
		int maxx = 99;
		int maxy = 99;
		int facing = 0; // 0,1,2,3 for N,E,S,W
		for (int i = 0; i < input.length(); i++) {
			char c = input.charAt(i);
			if (c == 'L') {
				facing = (4+facing-1)%4;
			} else if (c == 'R') {
				facing = (facing+1)%4;
			} else {
				// move
				if (c != 'M') {
					a[y][x] = c;
				}
				//System.out.println("a["+x+"]["+y+"] = "+a[y][x]);
				//System.out.println(facing);
				if (facing == 0) {
					y--;
				} else if (facing == 1) {
					x++;
				} else if (facing == 2) {
					y++;
				} else if (facing == 3) {
					x--;
				}
				// check corners
				if (x < minx) {
					minx = x;
				}
				if (y < miny) {
					miny = y;
				}
				if (x > maxx) {
					maxx = x;
				}
				if (y > maxy) {
					maxy = y;
				}
			}
		}
		System.out.println("minx: "+minx+" miny: "+miny+" maxx: "+maxx+" maxy: "+maxy);
		String ans = "";
		boolean trimleft = false;
		for (int col = miny; col < maxy+1; col++) {
			for (int row = minx; row < maxx+1; row++) {
				line += a[col][row];
			}
			ans += "\n";
		}
		System.out.println(ans);
		// for (int col = 0; col < a.length; col++) {
		// 	String line = "";
		// 	for (int row = 0; row < a[0].length; row++) {
		// 		line += a[col][row];
		// 	}
		// 	System.out.println(line);
		// }
	}
	
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		String turtle = "";
		while (s.hasNextLine()) {
			String line = s.nextLine();
			if (line.length() > 4 &&
				line.substring(0,2).equals("--") &&
				line.substring(line.length()-2,line.length()).equals("--")) {
				System.out.println(line);
				System.out.println();
			} else if (line.equals(".")) {
				draw(turtle); // call to above method
				turtle = "";
				System.out.println();
			} else {
				turtle += line;
			}
		}
	}
}