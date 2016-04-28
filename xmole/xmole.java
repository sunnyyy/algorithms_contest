import java.util.Scanner;
import java.util.ArrayList;
import java.text.NumberFormat;
import java.awt.geom.Line2D;

public class xmole {

	public static String xmole(ArrayList<String> chunk) {
		NumberFormat ff = new DecimalFormat("#0000000000");
		NumberFormat f = new DecimalFormat("#000000.000");
		int iters = 1;
		double xmin = 0;
		double xmax = 1000;
		double ymin = 0;
		double ymax = 1000;
		System.out.println(ff.format(iters)+f.format(xmin)+f.format(xmax)+f.format(ymin)+f.format(ymax));
		for (String line: chunk.iterator()) {
			iters++;
			// split line by whitespace
			String[] abc = line.split("\\s+");
			// get line elements
			double a = Double.parseDouble(abc[0]);
			double b = Double.parseDouble(abc[1]);
			double c = Double.parseDouble(abc[2]);
			double y_intercept = c/b;
			double x_intercept = c/a;
			// check that the line intersects the yard
			if (Line2D.linesIntersect(0,y_intercept,x_intercept,0,0,0,1000,0) ||
				Line2D.linesIntersect(0,y_intercept,x_intercept,0,0,0,0,1000) ||
				Line2D.linesIntersect(0,y_intercept,x_intercept,0,0,1000,1000,1000) ||
				Line2D.linesIntersect(0,y_intercept,x_intercept,0,1000,0,1000,1000)) {

				// MORE CODE HERE

				System.out.println(ff.format(iters)+f.format(xmin)+f.format(xmax)+f.format(ymin)+f.format(ymax));
			}
		}
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		ArrayList<String> chunk = new ArrayList<String>();
		while (scanner.hasNextLine()) {
			line = scan.nextLine();
			if (line.substring(0,2).equals("--")) {
				System.out.println(line);
			} else if (line.equals("*")) {
				System.out.println(line);
				String x = xmole(chunk);
				chunk.clear();
			} else {
				chunk.add(line);
			}
		}
	}

}