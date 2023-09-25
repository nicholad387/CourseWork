/*******************************************************************************
* Name        : shortestpath.cpp
* Author      : Nicholas Mohamed
* Date        : 12/07/22
* Description : Find all shortest paths using Floyd's algorithm
* Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

long **dist;
long **path_length;
long **next_vert;
int num_vert;
long INF = numeric_limits<long>::max();



int len(long val) {
	int digits = 1;
	while (val > 9) {
		val /= 10;
		digits++;
	}
	return digits;
}

/**
* Displays the matrix as a table.
to display a matrix of long values in a grid. The matrix parameter is a 2D array of longs, and the label parameter is a string that is displayed before the matrix. The use_letters parameter is a boolean that, if set to true, will display the values in the matrix as letters instead of numbers.

The function first finds the maximum value in the matrix that is not equal to INF, and uses this value to determine the width of each cell in the grid. It then prints the label, followed by a grid where the rows and columns are labeled with letters. Each cell in the grid is left-aligned and displays the value at the corresponding position in the matrix. If the value is INF, it is displayed as a dash (-), otherwise it is displayed as a number or a letter, depending on the value of the use_letters parameter.
*/
void display(long** const matrix, const string &label, const bool use_letters = false) {
	
	cout << label << endl;
	long max_val = 0;
	
	for (int i = 0; i < num_vert; i++) {
		for (int j = 0; j < num_vert; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	
	int cell_width = len(max(static_cast<long>(num_vert), max_val));
	
	cout << ' ';
	
	for (int j = 0; j < num_vert; j++) {
		cout << setw(cell_width + 1) << static_cast<char>(j + 'A');
	}
	
	cout << endl;
	
	for (int i = 0; i < num_vert; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vert; j++) {
			cout << " " << setw(cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

vector<char> path(int i, int j){
	
	if (next_vert[i][j] != INF){
		int next = next_vert[i][j];
		vector<char> start_int = path(i, next);
		vector<char> int_stop = path(next, j);
		int_stop.insert(int_stop.end(), 1 + start_int.begin(), start_int.end());
		return int_stop;
	} else {		// no next vertex
		char start = 65 + i;
		char stop = 65 + j;
		vector<char> path;
		path.push_back(stop);
		if (start == stop){	// don't add
			return path;
		} else {
			path.push_back(start);
			return path;
		}
	}
}

/**
a recursive function that calculates a path between two vertices in a graph. The i and j parameters are the indices of the starting and ending vertices, respectively, in the graph. The function returns a vector of characters representing the path from vertex i to vertex j.

The function uses the next_vert matrix to determine the next vertex on the path. If the value of next_vert[i][j] is not INF, then the function recursively calculates the path from i to the next vertex, and from the next vertex to j, and then combines these two paths into a single path. If the value of next_vert[i][j] is INF, then there is no next vertex and the function simply returns a vector containing the starting and ending vertices.

In either case, the path is returned as a vector of characters, where each character represents a vertex in the graph. The vertices are represented by the corresponding uppercase letters, starting with 'A' for the first vertex, 'B' for the second vertex, and so on.
**/

// displays the paths
void display_paths(){
	
	for (int i = 0; i < num_vert; i++){
		for (int j = 0; j < num_vert; j++){
			vector<char> curr_path = path(i, j);
			if (path_length[i][j] >= INF){
				cout << (char)(i + 65) << " -> " << (char)(j + 65) << ", distance: infinity, path: none" << endl;
			} else {
				ostringstream oss;
				for (int i = (int)curr_path.size() - 1; i >= 0; i--){
					if (i == (int)curr_path.size() - 1){
						oss << curr_path[i];
					} else {
						oss << " -> " << curr_path[i];
					}
				}
				string print_path = oss.str();
				cout << (char)(i + 65) << " -> " << (char)(j + 65) << ", distance: " << path_length[i][j] << ", path: " << print_path << endl;
			}
		}
	}
}

/**
This function displays the paths and distances between all pairs of vertices in a graph. It uses the path function to calculate the path between each pair of vertices, and the path_length matrix to determine the distance between each pair of vertices.

The function first iterates over all pairs of vertices, and for each pair, it calculates the path using the path function and retrieves the distance from the path_length matrix. If the distance is INF, then the function prints a message indicating that there is no path between the vertices. Otherwise, the function formats the path and distance and prints them.

The path is printed as a series of vertex names, separated by " -> ", starting with the ending vertex and ending with the starting vertex. The distance is printed as a number. This function is useful for displaying the results of a shortest path calculation.
**/

vector<string> chop(const string& s, const string& delim, const bool keep_empty = true) {
	
	vector<string> the_chop;
	
	if (delim.empty()) {
		the_chop.push_back(s);
		return the_chop;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty()) {
			the_chop.push_back(temp);
		}
		if (subend == s.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return the_chop;
}

/**
This function splits a string into a list of substrings using a specified delimiter string. The s parameter is the string to split, the delim parameter is the delimiter string, and the keep_empty parameter is a boolean that determines whether empty substrings should be included in the list of substrings.

The function first checks if the delimiter string is empty. If it is, then the input string is returned as a single-element list. Otherwise, the function iterates over the input string, using the search function to find instances of the delimiter string. For each instance of the delimiter, the function creates a substring consisting of the characters between the previous delimiter and the current delimiter. If keep_empty is true or the substring is non-empty, the substring is added to the list of substrings.

Once all instances of the delimiter have been found, the function returns the list of substrings. This function is useful for parsing a string that contains multiple values separated by a specific delimiter.
**/

//check for correct number of arguments and illegal values
bool data_check(vector<string> &parts, const int line_num, const string line, int last_vert) {
	
	bool correct = true;
	if (parts.size() != 3){		// check for to many or too few arguments
		cerr << "Error: Invalid edge data '"<< line << "' on line " << line_num << "." << endl;
		return false;
	}
	if (parts[0].length() > 1 || (parts[0][0] < 65 || parts[0][0] > last_vert)){	//if multiple characters or outside of possible vertex range, throw error
		cerr << "Error: Starting vertex '"<< parts[0] << "' on line " << line_num << " is not among valid values A-" << (char)last_vert << "." << endl;
		return false;
	}
	if (parts[1].length() > 1 || (parts[1][0] < 65 || parts[1][0] > last_vert)){	//if multiple characters or outside of possible vertex range, throw error
		cerr << "Error: Ending vertex '"<< parts[1] << "' on line " << line_num << " is not among valid values A-" << (char)last_vert << "." << endl;
		return false;
	}
	return correct;
}


long** new_matrix(const bool the_distance){
	
	long **matrix = new long*[num_vert];
	for (int i = 0; i < num_vert; i++){
		matrix[i] = new long[num_vert];
		for (int j = 0; j < num_vert; j++){
			if (j == i && the_distance == true){	// distance matrix set pivots to 0
				matrix[i][j] = 0;
			} else {
				matrix[i][j] = INF;		// values of matrix are infinity
			}
		}
	}
	return matrix;
}

void floyds_algorithm(){
	next_vert = new_matrix(false);
	
	for (int k = 1; k <= num_vert; k++){
		for (int i = 1; i <= num_vert; i++){
			for (int j = 1; j <= num_vert; j++){
				if (path_length[i - 1][k - 1] != INF && path_length[k - 1][j - 1] != INF){
					long right = path_length[i - 1][k - 1] + path_length[k - 1][j - 1];
					if (path_length[i - 1][j - 1] > right){
						path_length[i - 1][j - 1] = right;
						next_vert[i - 1][j - 1] = k - 1;
					}
				}
			}
		}
	}
}
/**
This function implements the Floyd-Warshall algorithm for calculating the shortest paths between all pairs of vertices in a graph. The next_vert and path_length matrices are used to store the intermediate results of the calculation.

The Floyd-Warshall algorithm is a dynamic programming algorithm that uses a three-nested loop to iterate over all pairs of vertices in the graph. For each pair of vertices i and j, the algorithm calculates the length of the shortest path between i and j that uses vertex k as an intermediate vertex. If this length is less than the current shortest path length between i and j, then the algorithm updates the path_length matrix and the next_vert matrix to reflect the new shortest path.

Once the algorithm has considered all possible intermediate vertices k, the path_length matrix will contain the shortest path lengths between all pairs of vertices, and the next_vert matrix will contain the next vertex on the shortest path between each pair of vertices. This function is useful for calculating the shortest paths between all pairs of vertices in a graph.
**/

// delete matrix
void delete_matrix(long** matrix){
	for (int i = 0; i < num_vert; i++){
		delete [] matrix[i];
	}
	delete [] matrix;
}

int main(int argc, const char *argv[]) {
	
	if(argc != 2){		// correct num of command line arguments
		cerr << "Usage: ./shortestpaths <filename>" << endl;
		return 1;
	}
	
	ifstream input_file(argv[1]); 
	if (!input_file) {      // check if file exist
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	
	input_file.exceptions(ifstream::badbit);
	
	string line;
	getline(input_file, line);
	line.erase(0, line.find_first_not_of(" "));		//remove spaces on left
	line.erase(line.find_last_not_of(" ") + 1);		//remove spaces on right
	
	istringstream check;
	check.str(line);
	
	if(!(check >> num_vert) || (num_vert < 1 || num_vert > 26)){		//checks that first line is an integer and in required range
		cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
		return 1;
	}
	int last_vert = num_vert + 64;	
	dist = new_matrix(true);
	
	
	try {
		unsigned int line_num = 2;
		while (getline(input_file, line)) {
			line.erase(0, line.find_first_not_of(" "));		//remove spaces on left
			line.erase(line.find_last_not_of(" ") + 1);		//remove spaces on right
			vector<string> parts = chop(line, " ");
			if(!data_check(parts, line_num, line, last_vert)){
				delete_matrix(dist);
				return 1;
			}
			
			int weight;
			istringstream temp2;
			temp2.str(parts[2]);
			if (!(temp2 >> weight) || weight < 1) {		//checks if weight is an integer and greater than 0
				cerr << "Error: Invalid edge weight '" << parts[2] << "' on line " << line_num << "." << endl;
				delete_matrix(dist);
				return 1;
			}
			dist[parts[0][0] - 65][parts[1][0] - 65] = weight;  //adds weight to dist
			line_num++;
		}
		input_file.close();  
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		delete_matrix(dist);
		return 1;
	}
	
	
	path_length = new long*[num_vert];
	for (int i = 0; i < num_vert; i++){
		path_length[i] = new long[num_vert];
		for (int j = 0; j < num_vert; j++){
			path_length[i][j] = dist[i][j];
		}
	}
	
	floyds_algorithm();
	
	//display 
	display(dist, "Distance matrix:");
	display(path_length, "Path lengths:");
	display(next_vert, "Intermediate vertices:", true);
	display_paths();
	
	
	//delete everything
	delete_matrix(dist);
	delete_matrix(path_length);
	delete_matrix(next_vert);
	
	return 0;
}