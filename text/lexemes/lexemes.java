import java.util.Scanner;
import java.util.HashMap;

public class lexemes {

    public static void lex(String in) {
        HashMap<Character,Character> hm = new HashMap<Character,Character>();
		char[] s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
		char[] o = "+-*/=.".toCharArray();
		char[] n = "1234567890".toCharArray();
		char[] p = "(),;".toCharArray();
		for (int i = 0; i < s.length; i++) {
			hm.put(s[i],'s');
		}
		for (int i = 0; i < o.length; i++) {
			hm.put(o[i],'o');
		}
		for (int i = 0;i < n.length; i++) {
			hm.put(n[i],'n');
		}
		for (int i = 0;i < p.length; i++) {
			hm.put(p[i],'p');
		}
		hm.put(' ','w');
		//hm.put();
		//String nin = "";
		String out = "";
		boolean quote = false;
		boolean num = false;
		boolean diff = true;
		for (int i = 0; i < in.length(); i++) {
			char c = in.charAt(i);
			char type = 'i';
			if (hm.get(c) != null) {
				type = hm.get(c);
			}

			if (quote) {
				if (c == '"') {
					// end quote
					quote = false;
				} else {
					// in quote
					out += "q";
					continue;
				}
			} else if (c == '"') {
				// start quote
				out += "q";
				quote = true;
			} else if (num) {
				if (type == 'n') {
					// c is number
					out += "n";
				} else if (c == '.') {
					if (i < in.length()-1 && hm.get(in.charAt(i+1))=='n') {
						// . is number
						out += "n";
					} else {
						// . is not number
						out += type;
						num = false;
			    	}
				} else {
					out += type;
					num = false;
				}
			} else if (c == 'n') {
				out += "n";
				num = true;
			} else {
				out += type;
			}
		}
		String in2 = "";
		String out2 = "";
		for (int j = 0; j < out.length()-1; j++) {
			in2 += in.charAt(j);
			out2 += out.charAt(j);
			if (out.charAt(j) != out.charAt(j+1)) {
				in2 += '|';
				out2 += ' ';
			}
			
		}
		in2 += in.charAt(out.length()-1);
		out2 += out.charAt(out.length()-1);
		System.out.println(in2);
		System.out.println(out2);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextLine()) {
			lex(sc.nextLine());

		}
	}

}


