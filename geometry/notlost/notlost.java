import java.util.*;
import java.io.*;
import java.lang.Math;

public class notlost {
    
    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	double x = 0;
	double y = 0;
	while (scan.hasNextLine()) {
	    String s = scan.nextLine();
	    //double x = 0;
	    //double y = 0;
	    if (s.charAt(0) == '-') {
		System.out.println(s);
	    } else if (s.charAt(0) == '*') {
		double ans_deg = 0;
		if (x>0 && y>0) {
		    ans_deg=90-(Math.toDegrees(Math.atan2(y,x))%360);
		} else if (x<0 &&y >0){
		    ans_deg=450-(Math.toDegrees(Math.atan2(y,x))%360);
		} else if(x<0 && y<0){
		    ans_deg=450-(Math.toDegrees(Math.atan2(y,x))%360);
		}else if(x>0 && y<0){
		    ans_deg=450-(Math.toDegrees(Math.atan2(y,x))%360);
		}
		
		double ans_dist = Math.round(Math.sqrt(x*x+y*y));
		x = 0;
		y = 0;
		System.out.println((int)ans_deg + " " + (int)ans_dist);
	    } else {
		String[] a = s.split("\\s+");
		//System.out.println(a[0]);
		//System.out.println(a[1]);
		double deg = Double.parseDouble(a[0]);
		int dist = Integer.parseInt(a[1]);
		double rad = Math.toRadians( (-deg) + 90);
		//System.out.println(rad);
		x += dist*Math.cos(rad);
		y += dist*Math.sin(rad);
		//System.out.println(x + " " + y);
	    }
	}
    }
    
}
