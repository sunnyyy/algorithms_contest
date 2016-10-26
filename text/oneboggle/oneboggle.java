import java.util.*;
import java.io.*;

public class oneboggle {

    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);

	HashSet<String> dict = new HashSet<>();
	boolean read_dict = true;
	
	while (scan.hasNextLine()) {
            String s = scan.nextLine();
	    if (s.contains("--")) {
		System.out.println(s);
	    } else if (s.charAt(0) == '*') {
		if (read_dict) {
		    read_dict = false;
		} else {
		    read_dict = true;
		}
	    } else {
		

		if (read_dict) {
		    dict.add(s);
		    String rev = "";
		    for (int i = s.length()-1; i >= 0; i--) {
			rev += s.charAt(i);
		    }
		    dict.add(rev);
		} else {
		    String ans = "";
		    for (int j = 0; j < s.length(); j++) {
			ans += '.';
		    }
		    for (int j = 0; j < s.length(); j++) {
			for (String d : dict) {
			    int f = s.indexOf(d,j);
			    if (f > -1) {
				ans = ans.substring(0,f) + d + ans.substring(f+d.length(), s.length());
			    }
			}
		    }
		    //for (String d : dict) {
			
		    //}
		    System.out.println(ans);
		}
	    }
	}
	
    }

}
