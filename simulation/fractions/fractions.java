import java.util.*;

public class fractions {

	public static String fra(String s) {
		boolean b = false;
		double f = Double.parseDouble(s);
		if (s.length() < 17) {
			int l = 17-s.length();
			for (int i = 0; i < l; i++) {
				s += "0";
			}
		}
		outer:
		for (int d = 1; d <= 1000; d++) {
			for (int n = 1; n <= d-1; n++) {
				if ( Math.abs(f - (double)n/d) < 0.0000000005 ) {
					b = true;
					s += " " + n + "/" + d;
					break outer;
				}
			}
		}
		if (b == false) {
			s += " -";
		}
		return s;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextLine()) {
			System.out.println(fra(sc.nextLine()));
		}
	}

}
