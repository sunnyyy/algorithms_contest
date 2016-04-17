import java.util.*;

public class piglatin {

	public static Set<Character> vowels = new HashSet<Character>();

	public static String pig(String word, Set<Character> vowels) {
		if (vowels.contains(word.charAt(0))) {
			return word+"ay";
		} else {
			return word.substring(1,word.length()) + word.substring(0,1) + "ay";
		}
	}

	public static void main(String[] args) {	
		vowels.add('a');
		vowels.add('e');
		vowels.add('i');
		vowels.add('o');
		vowels.add('u');
		vowels.add('y');
		Scanner r = new Scanner(System.in);
		while (r.hasNextLine()) {
			System.out.println(pig(r.nextLine(),vowels));
		}
	}
}