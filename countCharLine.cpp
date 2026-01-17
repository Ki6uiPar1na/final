// read a text file and show total words and lines in this text file
#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("input.txt");
    int lines = 0, words = 0;
	string line;

	while (getline(in, line)) {
		++lines;
		// count words in the line using istringstream (splits on whitespace)
		istringstream iss(line);
		string token;
		while (iss >> token) ++words;
	}

	cout << "Total lines: " << lines << "\n";
	cout << "Total words: " << words << "\n";

	return 0;
}
