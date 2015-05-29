/*
 * Read_file.h
 *
 *  Created on: 21/05/2015
 *      Author: Miguel
 */

#ifndef SRC_READDIR_H_
#define SRC_READDIR_H_

#include <vector>
#include <string>
#include <dirent.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
class readDir {
private:
	vector<string> filenames;
	vector<vector<int> > compressed;
public:
	vector<string> getFilenames();
	vector<vector<int> > getCompressed();
	void addCompressed(vector<int> compress);
	vector<int>::iterator accessCompressBegin(int i){
		return compressed.at(i).begin();
	}
	vector<int>::iterator accessCompressEnd(int i){
		return compressed.at(i).end();
	}
	int readDirectories(char* directory);
};
#endif /* SRC_READDIR_H_ */

