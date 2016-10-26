import java.util.Scanner;
import java.util.HashMap;

/* ********************************************************************************
* Implement a very simple FSM that checks a bit sequence.
* Input: #1 is the state, #2 is the next state if 0, #3 is the next state if 1.
*
Sample Input
------ -----

-- RECOGNIZE '10' --
$ $ A
A * A
* $ A
.
0000
1111
0100
010010100
0100110011100111100
.

Sample Output
------ ------

-- RECOGNIZE '10' --
0000
$$$$$
1111
$AAAA
0100
$$A*$
010010100
$$A*$A*A*$
0100110011100111100
$$A*$AA*$AAA*$AAAA*$
******************************************************************************** */
public class simplefsm {


	public static String simple(HashMap<String, String> fsm, String line, String start_state) {
		String result = start_state;
		String current_state = start_state;
		for (int i = 0; i < line.length(); i++) {
			if (line.charAt(i)=='0') {
				current_state = fsm.get(current_state).substring(0,1);
			} else {
				current_state = fsm.get(current_state).substring(2,3);
			}
			result += current_state;
		}
		return result;
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		HashMap<String, String> fsm = new HashMap<String, String>();
		boolean bool_fsm = true;
		boolean start_fsm = false;
		String start_state = "";
		while (scan.hasNextLine()) {
			String line = scan.nextLine();
			if (line.substring(0,2).equals("--")) {
				System.out.println(line);
				fsm.clear();
				start_fsm = true;
			} else if (line.equals(".")) {
				if (bool_fsm) {
					bool_fsm = false;
				} else {
					bool_fsm = true;
				}
			} else {
				if (bool_fsm) {
					if (start_fsm) {
						start_symbol = line.substring(0,1);
						start_fsm = false;
					}
					// ex: line is "$ $ A", so key is "$" and value is "$ A"
					fsm.put(line.substring(0,1), line.substring(2,4));
				} else {
					// print line and result
					System.out.println(line);
					System.out.println(simple(fsm, line, start_state);
				}
			}
		}
	}

}