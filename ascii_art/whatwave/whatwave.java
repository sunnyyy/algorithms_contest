import java.util.*;
import java.io.*;
import java.lang.*;
public class whatwave {
    private static int period(char[] l){
	int count = 0;
	int ind = 0;
	char firstChar = l[0];
	char charOther;
	if (firstChar==' '){
	    charOther='x';
	} else {
	    charOther=' ';
	}
	while (l[ind] != charOther){
	    ind++;
	}
	while (l[ind] != firstChar){
	    count++;
	    ind++;
	}
	while (l[ind] != charOther){
	    count++;
	    ind++;
	}
	return count;
    }

    public static void main(String[] args) {
	Scanner s = new Scanner(System.in);
	while (s.hasNextLine()) {
	    String waveType = "";
	    int numXLines = 1;	
	    System.out.println(s.nextLine());// ---- SAMPLE -----
	    int period = period(s.nextLine().toCharArray()); // first line used for period
	    String str = s.nextLine();
	    if (str.equals("*")){//singleton case
		System.out.println("square " + period);
	    } else {
		while (s.hasNextLine() && !str.contains("*")){
		    if (str.contains("x")){
			numXLines++;
		    }
		    str = s.nextLine();
		}
	        if (numXLines == 2) {
		    System.out.println("square " + period);
		} else {                              	       
		    System.out.println("sine " + period);
		}
	    }
	}
    }
}
