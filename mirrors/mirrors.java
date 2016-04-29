import java.util.Scanner;
import java.util.ArrayList;

public class mirrors {

	public static void mirror(String mirror_line, ArrayList<String> pts) {
		String[] mirror = mirror_line.split("\\s+");
		double x1 = mirror[0];
		double x2 = mirror[1];
		double y1 = mirror[2];
		double y2 = mirror[3];
		NumberFormat nf = new NumberFormat("#00000.000");
		for (String point: pts) {
			String[] xy = point.split("\\s+");
			double x = Double.parseDouble(xy[0]);
			double y = Double.parseDouble(xy[1]);
			double xx;
			double yy;
			System.out.println(nf.format(x)+nf.format(y)+nf.format(xx)+nf.format(yy));
		}
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		String mirror_line = ""
		ArrayList<String> pts = new ArrayList<String>();
		while (scan.hasNextLine()) {
			line = scan.nextLine();
			if (line.substring(0, 2).equals("--")) {
				System.out.println(line);
				mirror_line = scan.nextLine();
			} else if (line.equals("*")) {
				System.out.println(line);
				mirror(mirror_line, pts);
				pts.clear();
			} else {
				pts.add(line);
			}
		}
	}

}