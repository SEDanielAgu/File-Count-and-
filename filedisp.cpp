#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[]) {
    string outputOne;	// creates a string for the next lines
    string outputTwo;
    string outputThree;

    string d = "directories";	// strings for comparisons
    string f = "files";
    string b = "bytes";

    getline(cin, outputOne); // reads standard input
    getline(cin, outputTwo);
    getline(cin, outputThree);

    string arg = argv[1]; // captures the option

    if ((arg == "-d") && (outputOne.find(d)) != string::npos) { 
	cout << outputOne << endl;
    } else if ((arg == "-f") && (outputTwo.find(f)) != string::npos) {
	cout << outputTwo << endl;
    } else if ((arg == "-b") && (outputThree.find(b)) != string::npos) {
	cout << outputThree << endl;
    } else {
	cout << "Error: Incorrect input" << endl;
    }
    return 0;
}
