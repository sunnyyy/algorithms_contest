import java.util.Scanner;

public class buffalo {

    public static String buf(String[] a) {
	String s = "";
	int x1 = Integer.parseInt(a[0]);
	int y1 = Integer.parseInt(a[1]);
	int x2 = Integer.parseInt(a[2]);
	int y2 = Integer.parseInt(a[3]);
	int x3 = Integer.parseInt(a[4]);
	int y3 = Integer.parseInt(a[5]);
	int xi = Integer.parseInt(a[6]);
	int yi = Integer.parseInt(a[7]);
	int p12 = (x2 - x1) * (yi - y1) - (y2 - y1) * (xi - x1);
	int p23 = (x3 - x2) * (yi - y2) - (y3 - y2) * (xi - x2);
	int p31 = (x1 - x3) * (yi - y3) - (y1 - y3) * (xi - x3);
	int[] b = {p12, p23, p31};
	for (int i = 0; i < 3; i++) {
		if (b[i] < 0) {
			s += "R";
		} else {
			s += "L";
		}
	}
	return s;
    }

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		while (s.hasNextLine()) {
			String[] a = s.nextLine().split(" ");
			System.out.println(buf(a));
		}
	}

}
