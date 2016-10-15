import java.util.Scanner;
//import java.util.Set;

public class lcddisplay {

	public static void display(int s, String str) {
		int h = 2*s+3;
		int w = s+2;
		int ww = (s+2)*str.length() + str.length()-1;
		int m = h/2+1;
		// initialize char double array
		char[][] c = new char[h][ww];
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < ww; j++) {
				c[i][j] = ' ';
			}
		}
		// change display, going by number, and then clockwise
		for (int si = 0; si < str.length(); si++) {
			int n = Integer.parseInt(str.substring(si, si+1));
			int index = si*(w+1);
			// group 1: upper horz line
			if (!(n==1||n==4)) {
				for (int j = 1; j < w-1; j++) {
					c[0][index+j] = '-';
				}
			}
			// group 2: upper right vert line
			if (!(n==5||n==6)) {
				for (int i = 1; i < m; i++) {
					c[i][index+w-2] = '|';
				}
			}
			// group 3: lower right vert line
			if (!(n==2)) {
				for (int i = m+1; i < h-1; i++) {
					c[i][index+w-2] = "|";
				}
			}
			// group 4: lower horz line
			if (!(n==1||n==4||n==7)) {
				for (int j = 1; j < w-1; j++) {
					c[h-1][index+j] = '-';
				}
			}
			// group 5: lower left line
			if (n==2||n==6||n==8||n==0) {
				for (int i = m+1; i < h-1; i++) {
					c[i][index] = '|';
				}
			}
			// group 6: upper left line
			if (!(n==1||n==2||n==3||n==7)) {
				for (int i = 1; i < m; i++) {
					c[i][index] = '|';
				}
			}
			// group 7: middle horz line
			if (!(n==1||n==7)) {
				for (int j = 1; j < w-1; j++) {
					c[i][index+j] = '-';
				}
			}
		}
		// print
		for (int i = 0; i < h; i++) {
			String line = "";
			for (int j = 0; j < ww; j++) {
				line += c[i][j];
			}
			System.out.println(line);
		}
		System.out.println();
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		while (scan.hasNextLine()) {
		    String line = scan.nextLine();
		    String[] a = line.split("\\s+");
		    display(Integer.parseInt(a[0], a[1]));
		}
	}

}
