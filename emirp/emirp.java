import java.util.Scanner;

public class emirp {

	public static boolean prime(int n) {
		for (int i = 0; i < Math.sqrt(n); i++) {
			if (n%i == 0) {
				return false;
			}
		}
		return true;
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		while (scan.hasNextLine()) {
		    String line = scan.nextLine();
		    String rev = "";
		    for (int i = line.length()-1; i >= 0; i--) {
		    	rev += line.charAt(i);
		    }
		    int n = Integer.parseInt(rev);
		    boolean emirp = prime(n);
		    if (emirp == true) {
		    	System.out.println(1);
		    } else {
		    	SYstem.out.println(0);
		    }
		}
	}

}
