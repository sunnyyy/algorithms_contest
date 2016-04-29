import java.util.Scanner;
import java.util.Math;

/* ********************************************************************************
* From geometry_problems_index.pdf
*
* Given points A, B, C, figure out whether C is closer to A, B, or the ZoomTube
* (line between A & B). To do this, translate rotate the xy-coordinate system to
* make a new x'y'-coordinate system in which A has x'y'-coordinates (0,0) and B has 
* x'y'-coordinates (L,0), where L is the distance from A to B. Then the answer can 
* be easily read from the x’ coordinate of C.
* 
* Input
* -----
* For each of several cases, one line, containing
* Ax Ay Bx By Cx Cy
* 
* Output
* ------
* For each case one line containing:
* (Cx',Cy') L ANS
* where ANS is one of: A, B, or ZoomTube
* The x'y'-coordinates and L must be accurate to plus or minus 0.001.
* 
Sample Input
------ -----
0 0 1 0 0.5 -6
5.0 3.0 5.5 2.5 5.0 4.0
5.0 3.0 5.5 2.5 5.0 1.0

Sample Output
------ ------
(0.500,-6.000) 1.000 ZoomTube
(-0.707,0.707) 0.707 A
(1.414,-1.414) 0.707 B
******************************************************************************** */
public class changeview {

	public static void closest(String line) {
		// get values from line
		String[] temp = line.split("\\s+");
		double ax = Double.parseInt(temp[0]);
		double ay = Double.parseInt(temp[1]);
		double bx = Double.parseInt(temp[2]);
		double by = Double.parseInt(temp[3]);
		double cx = Double.parseInt(temp[4]);
		double cy = Double.parseInt(temp[5]);
		// calculate length of a to b
		double lab = Math.sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));
		// convoluted steps with triangle formulas to calculate height (cyy)
		double lac = Math.sqrt((cx-ax)*(cx-ax)+(cy-ay)*(cy-ay)); // length a to c
		double lbc = Math.sqrt((cx-bx)*(cx-bx)+(cy-by)*(cy-by)); // length b to c
		double s = (lab+lac+lbc)/2;
		double area = Math.sqrt(s*(s-lab)*(s-lac)*(s-lbc));
		// finally get cxx & cyy
		double cyy = area*2/lab;
		double cxx = Math.sqrt(lac*lac - cyy*cyy);
		// signs of cxx
		// using linear algebra, if cy is on right side of zoomtube, cyy is neg
		if ((bx-ax)*(cy-ay)-(by-ay)*(cx-ax) < 0) {
			cyy = -1*cyy;
		}
		// sign of cyy
		// looking at original pts, possible scenarios for cxx relative to origin:
		// if ax==bx && by>ay --> vert line going up --> cxx is neg if cy<ay
		// if ax==bx && by<ay --> vert line going down --> cxx is neg if cy>ay
		// if ax<bx --> line going right-ish --> cxx is neg if cx<ax
		// if ax>bx --> line going left-ish --> cxx is neg if cx>ax
		if ((ax==bx && by>ay && cy<ay) || (ax==bx && by<ay && cy>ay) ||
			(ax<by && cx<ax) || (ax>by && cx<ax)) {
			cxx = -1*cxx;
		}
		// get closest point
		String loc = "";
		if (cxx <= 0) {
			loc = "A";
		} else if (cxx >= lab) {
			loc = "B";
		} else {
			loc = "ZoomTube";
		}
		// print result
		NumberFormat nf = new NumberFormat("#0.000");
		System.out.println("("+nf.format(cxx)+","+nf.format(cyy)+") "+nf.format(l)+" "+loc);
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		while (scanner.hasNextLine()) {
			closest(scan.nextLine());	
		}
	}

}