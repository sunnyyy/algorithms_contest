import java.util.Scanner;
import java.util.ArrayList;
import java.util.Set;
import java.util.HashMap;

public class electriccars {
	
	public static int[][] initialize_graph(int n) {
		// initialize empty graph
		// assume edge of length "infinity" = no edge
		int[][] g = new int[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				g[i][j] = Integer.MAX_VALUE;
			}
		}
	}

	public static int[][] add_edges(int[][] g, HashMap<String, Integer> node_i,
		ArrayList<String> edges) {
		// insert edges
		for (String edge: edges.iterator()) {
			String[] e = edge.split(",");
			assert e.length==3;
			// bidirectional
			g[node_i.get(e[0])][node_i.get(e[1])] = Integer.parseInt(e[2]);
			g[node_i.get(e[1])][node_i.get(e[0])] = Integer.parseInt(e[2]);
		}
		return g;
	}

	// partial implementation of https://gist.github.com/econchick/4666413
	public static int dijkstra(int[][] dists, int start_i, int end_i, int range) {
		// key = visited nodes, value = weight from start to end
		HashMap<Integer, Integer> visited = new HashMap<Integer, Integer>();
		visited.put(start_i, 0);
		// nodes in graph, in index form
		Set<Integer> nodes = new Set<Integer>();
		for (int i = 0; i < dists.length; i++) {
			nodes.add(i);
		}
		
		while (nodes.size() > 0) {
			int min_node = -1; // treat this as null
			for (int node: nodes.iterator()) {
				if (min_node == -1) {
					min_node = node;
				} else if (visited.containsKey(node) && visited.get(node) < visited.get(min_node)) {
					min_node = node;
				}
			}
			if (min_node == -1) {
				break;
			}
			nodes.remove(min_node);

			int curr_weight = visited.get(min_node)
			for (int adj = 0; adj < dists[min_node].length; adj++) {
				// consider it an edge if less than MAX_VALUE;
				if (dists[min_node][adj] < Integer.MAX_VALUE) {
					int weight = curr_weight + dists[min_node][adj];
					if (!visited.containsKey(adj) || weight < visited.get(adj)) {
						visited.put(adj) = weight;
					}
				}
			}
		}
		if (visited.containsKey(end_i) && visited.get(end_i) < range) {
			return visited.get(end_i);
		} else {
			return -1;
		}
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		// input is in one of four modes
		boolean b_range = true;
		boolean b_nodes = false;
		boolean b_num_e = false;
		boolean b_other = false;
		// if range is 0, exit
		boolean exit = false;
		// initialize things
		int range = 0;
		String nodes = "";
		ArrayList<String> edges = new ArrayList<String>();
		ArrayList<String> trips = new ArrayList<String>();
		int i = 0;
		while (scan.hasNextLine() && !exit) {
			String line = scan.nextLine();
			// cycle through all four modes of one input group
			if (b_range) {
				range = Integer.parseInt(line);
				b_range = false;
				b_nodes = true;
				if (range==0) exit;
			} else if (b_nodes) {
				nodes = line;
				b_nodes = false;
				b_num_e = true;
			} else if (b_num_e) {
				num_edges = Integer.parseInt(line);
				b_num_e = false;
				b_other = true;
			} else if (b_other) {
				if (i < num_edges) {
					edges.add(line);
				} else {
					trips.add(line);
				}
			}
			// calculate trips for this graph
			if (line.equals(".")) {
				String[] snodes = nodes.split(",");
				HashMap<String, Integer> node_i = new HashMap<String, Integer>();
				for (int ni = 0; ni < snodes.length; ni++) {
					node_i.put(snodes[ni], ni);
				}
				int[][] g = initialize_graph(snodes.length);
				g = fill_edges(g, node_i);
				for (String trip: trips.iterator()) {
					int start_i = Integer.parseInt(trip.substring(0,1));
					int end_i = Integer.parseInt(trip.substring(2,3));
					System.out.println(dijkstra(g,start_i,end_i,range));
				}
				// reset things
				b_other = false;
				b_range = true;
				edges.clear();
				trips.clear();
				range = 0;
				nodes = "";
				i = 0;
			}
		}
	}

}
