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

class FileCnt {
public:			// class that holds the counts for the monitered variables
    int dirCount;	// initializes the variables
    int fileCount;
    int byteCount;

    FileCnt() {		// default constructor
        dirCount = 0;
        fileCount =0;
        byteCount = 0;
    }

    void traverse(string str) { // method that recursively traverses the given directory
        const char *c = str.c_str(); //capture the file path
	if (access(c, R_OK) == 0) { // checks if the user has read access skips otherwise
            DIR *pwd = opendir(c); // opens the directory
	    struct stat buf;
            struct dirent *dirRead;
            if (pwd != nullptr) { // makes sure the directory is not a null pointer
                while ((dirRead = readdir(pwd)) != nullptr) { // reads everything in the directory
			stat(dirRead->d_name, &buf);
		    if (strcmp(dirRead->d_name, ".") != 0 && strcmp(dirRead->d_name, "..") != 0) {
                         if (dirRead->d_type == DT_DIR) { // if directory
                            dirCount++; 		//increment count
                            char tmp[4096];		// buffer one to make the new path
                            char tmpTwo[4096];		// buffer two to make the new path
                            string newDir = strcpy(tmp, c);
                            string dirName = strcpy(tmpTwo,dirRead->d_name);
                            newDir += "/" + dirName;	// constructs the new file path 
                            traverse(newDir);		// recursively traverses the next directory
                        } else if (dirRead->d_type == DT_REG) { //if plain file
                            fileCount++;		// increment count
                            byteCount += buf.st_size;	// update the byte size
		        }
		    }    
                }  
            }  
	}
    }

    void print(string n) {	// creates print statements and writes them to standard outptut
        string lineOne = "The total number of directories in directory " + n + " is:   " + to_string(dirCount);
        string lineTwo = "The total number of files in directory " + n + " is:   " + to_string(fileCount);
        string lineThree = "The total number of bytes occupied by all files in directory " + n + " is:   " + to_string(byteCount);
        
	printf("%s \n", lineOne.c_str()); 
	printf("%s \n", lineTwo.c_str());
	printf("%s \n", lineThree.c_str());
    }
};

int main(int argc, char *argv[]) {
    char tmp[4096];
    strcpy(tmp, argv[1]); // captures the given file path
    FileCnt counter;	  // creates an instance of the object
    counter.traverse(tmp);
    counter.print(tmp);
    return 0;
}
