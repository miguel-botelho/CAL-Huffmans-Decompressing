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

class readDir {
private:
	std::vector<std::string> filenames;
	std::vector<std::vector<int> > compressed;
public:
	std::vector<std::string> getFilenames();
	std::vector<std::vector<int> > getCompressed();
	void addCompressed(std::vector<int> compress);
	std::vector<int>::iterator accessCompressBegin(int i){
		return compressed.at(i).begin();
	}
	std::vector<int>::iterator accessCompressEnd(int i){
		return compressed.at(i).end();
	}
	int readDirectories(char* directory);
};
#endif /* SRC_READDIR_H_ */

