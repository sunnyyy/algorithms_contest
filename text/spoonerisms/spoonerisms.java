import java.util.Scanner;
import java.util.Arrays;

public class spoonerisms {
    
    public static String spoon(String line) {
		String[] a = line.split("\\s+");
		String temp = a[0];
		int n = a.length-1;
		//char[] vowels = {'a','e','i','o','u'};
		char a0 = a[0].charAt(0);
		char an = a[n].charAt(0);
		if (a0=='a'||a0=='e'||a0=='i'||a0=='o'||a0=='u') {
		    if (an=='a'||an=='e'||an=='i'||an=='o'||an=='u') {
				// skip
		    } else {
				// first starts w vowel, last no
				// System.out.println("yoo");
				// a[0] = a[n].substring(0,1) + a[0];
				String anf = "";
				int i = 1;
				char ani = a[n].charAt(i);
				while (!(ani=='a'||ani=='e'||ani=='i'||ani=='o'||ani=='u'||ani=='y')) {
				    anf += ani;
				    i++;
				    ani = a[n].charAt(i);
				}
				a[0] = a[n].substring(0,1) + anf + a[0];
				a[n] = a[n].substring(i,a[n].length());
		    }
		} else {
		    if (an=='a'||an=='e'||an=='i'||an=='o'||an=='u') {
				// last starts w vowel, first no
				// System.out.println("fml");
				String a0f = "";
				int i = 1;
				char a0i = a[0].charAt(i);
				while (!(a0i=='a'||a0i=='e'||a0i=='i'||a0i=='o'||a0i=='u'||a0i=='y')) {
					a0f += a0i;
					i++;
					a0i= temp.charAt(i);
				}
				a[0] = a[0].substring(i,a[0].length());
				a[n] = temp.substring(0,1) + a0f + a[n];
			} else {
				// no vowels
				//a[0] = a[n].substring(0,1) + a[0].substring(1,a[0].length());
				//a[n] = temp.substring(0,1) + a[n].substring(1,a[n].length());
				String anf = "";
				int i = 1;
				char ani = a[n].charAt(i);
				while (!(ani=='a'||ani=='e'||ani=='i'||ani=='o'||ani=='u'||ani=='y')) {
					anf += ani;
					i++;
					ani = a[n].charAt(i);
				}
				String a0f = "";
				int j = 1;
				char a0j = a[0].charAt(j);
				while (!(a0j=='a'||a0j=='e'||a0j=='i'||a0j=='o'||a0j=='u'||a0j=='y')) {
					a0f += a0j;
					j++;
					a0j= temp.charAt(j);
				}
				a[0] = a[n].substring(0,1) + anf + a[0].substring(j,a[0].length());
				a[n] = temp.substring(0,1) + a0f + a[n].substring(i,a[n].length());
			}
		}
		return String.join(" ",a);
    }

    public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		while (s.hasNextLine()) {
			String line = s.nextLine();
			String sp = spoon(line);
			System.out.println(sp);
		}
    }

}
