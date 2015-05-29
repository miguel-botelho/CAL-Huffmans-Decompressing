/*
 * directory.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Miguel
 */

#include "readDir.h"


using namespace std;

int readDir::readDirectories(char * directory) {
	DIR *dir = opendir(directory);
	struct dirent *ent;

	if (dir != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
		  string temp = "";
		  temp = string(ent->d_name);
		  if (temp.find(".") != string::npos)
			  if (!(temp == "." || temp == ".."))
				  filenames.push_back(temp);
	  }
	  closedir (dir);
	} else {
		cout << "Could not read the directory" << endl;
	  return 1;
	}
	cout << "Directories read successfully!" << endl;
	return 0;
}

vector<string> readDir::getFilenames(){
	return filenames;
}

vector<vector<int> > readDir::getCompressed(){
	return compressed;
}

void readDir::addCompressed(vector<int> compress){
	compressed.push_back(compress);
}
