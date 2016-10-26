import java.util.*;
import java.io.*;

public class substrings {
    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	String dna = "";

	while (scan.hasNextLine()) {
	    String s = scan.nextLine();

	    if (s.charAt(0) == '-') {
		System.out.println(s);
	    } else if (s.charAt(0) == '*') {
		dna = "";
	    } else if (dna.length() == 0) {
		dna = s;
	    } else {
		int l = s.length();
		HashSet<Integer> a = new HashSet<>();
		for (int i = 0; i < dna.length(); i++) {
		    int f = dna.indexOf(s, i);
		    if (f > -1) a.add(f);
		}
		String ans = l + " " + a.size();
		for (Integer j : a) {
		    ans += " " + j;
		}
		System.out.println(ans);
	    }
	    
	}
    }
}
