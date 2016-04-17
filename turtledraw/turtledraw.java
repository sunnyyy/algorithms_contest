import java.util.Scanner;

public class turtledraw {

	public static void draw(String input) {
		char[][] a = new char[198][198];
		int x = 99;
		int y = 99;
		int nwx = 99;
		int nwy = 99;
		int sex = 99;
		int sey = 99;
		int facing = 0; // 0,1,2,3 for N,E,S,W
		for (int i = 0; i < input.length(); i++) {
			char c = input.charAt(i);
			if (c == 'L') {
				if (facing == 0) {
					facing = 3;
				} else {
					facing = (facing-1)%4;
				}
			} else if (c == 'R') {
				facing = (facing+1)%4;
			} else {
				// move
				a[x][y] = c;
				if (c == 'M') a[x][y] = ' ';
				if (facing == 0) {
					y--;
				} else if (facing == 1) {
					x++;
				} else if (facing == 2) {
					y++;
				} else {
					x--;
				}
				// check corners
				if (x < nwx) nwx = x;
				if (y < nwy) nwy = y;
				if (x > sex) sex = x; // unfortunate abbrev
				if (y > sey) sey = y;
			}
		}
		for (int i = nwy; i < sey+1; i++) {
			String line = "";
			for (int j = nwx; j < sex+1; i++) {
				line += a[i][j];
			}
			System.out.println(line);
		}
	}
	
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		String turtle = "";
		while (s.hasNextLine()) {
			String line = s.nextLine();
			if (line.substring(0,2)=="--") {
				System.out.println(line);
				System.out.println();
			} else if (line==".") {
				draw(turtle); // call to above method
				turtle = "";
				System.out.println(line);
				System.out.println();
			} else {
				turtle += line;
			}
		}
	}
}