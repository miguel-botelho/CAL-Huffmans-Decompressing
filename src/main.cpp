/*
 * main.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Miguel
 */

#include "readDir.h"
#include "huffman.h"
#include "lzw.h"
#include <algorithm>
#include <iterator>
#include <bitset>
#include <sstream>

using namespace std;

int main()
{

	readDir directories;
	directories.readDirectories("C:\\Users\\Miguel\\Desktop");

	/* COMPRESS */
	for (unsigned int i = 0; i < directories.getFilenames().size(); i++)
	{
		vector<int> compressed;


		string diretorioUtilizado;
		diretorioUtilizado = "C:\\Users\\Miguel\\Desktop";
		diretorioUtilizado.append("\\");
		diretorioUtilizado.append(directories.getFilenames().at(i).c_str());

		string diretorioComprimido;
		diretorioComprimido = "compressed_";
		diretorioComprimido.append(directories.getFilenames().at(i).c_str());

		ifstream temp;
		temp.open(diretorioUtilizado.c_str(), ios::binary);

		ofstream file;
		file.open(diretorioComprimido.c_str(), ios::binary);

		string conteudo;

		while (!(temp.eof()))
		{
			string temp1;
			getline(temp, temp1);
			conteudo.append(temp1);
		}

		compress(conteudo, back_inserter(compressed));

		directories.addCompressed(compressed);

		copy(compressed.begin(), compressed.end(), ostream_iterator<int>(file));

		temp.close();
		file.close();

		string decompressed = decompress(compressed.begin(), compressed.end());

		string decompressed_name = "decompressed_";
		decompressed_name.append(directories.getFilenames().at(i).c_str());

		ofstream decompressed_file;
		decompressed_file.open(decompressed_name.c_str());

		for (unsigned int j = 0; j < decompressed.length(); j++)
		{
			decompressed_file << decompressed.at(j);
		}

		decompressed_file.close();

	}

	return 0;
}

