import java.util.Scanner;
import java.util.Math;

public class pseudopi {

	public static void pi(String line) {
		String[] a = line.split("\\s+");
		int n = Integer.parseInt(a[0]);
		int mult = Integer.parseInt(a[1]);
		int mod = Integer.parseInt(a[2]);
		int seed = Integer.parseInt(a[3]);
		int rand = random(mult,seed,mod);
		int s = mod - 1;
		int m = 0;
		for (int i = 0; i < n; i++) {
			rand = random(mult,rand,mod);
			int rx = rand;
			rand = random(mult,rand,mod);
			int ry = rand;
			double x_dist = (rx+0.5)/s - 0.5;
			double y_dist = (ry+0.5)/s - 0.5;
			double dist_from_center = Math.sqrt(x_dist*x_dist + y_dist*y_dist);
			if (dist_from_center < 0.5) {
				m++;
			}
		}
		double est = ((double) m)/n;
		System.out.println(n+" "+mult+" "+mod+" "+seed+" "+est);
	}

	public static int random(mult, rand, mod) {
		return (mult * rand) % mod;
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		String mirror_line = ""
		ArrayList<String> pts = new ArrayList<String>();
		while (scan.hasNextLine()) {
			line = scan.nextLine();
			pi(line);
		}
	}

}