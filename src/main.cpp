/*
 * main.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Miguel
 */

#include "readDir.h"
#include "huffman.h"
#include "huffcoding.cpp"
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

	/* COMPRESS AND DECOMPRESS WITH LZW*/
	for (unsigned int i = 0; i < directories.getFilenames().size(); i++)
	{
		vector<int> compressed;

		string diretorioUtilizado;
		diretorioUtilizado = "C:\\Users\\Miguel\\Desktop";
		diretorioUtilizado.append("\\");
		diretorioUtilizado.append(directories.getFilenames().at(i).c_str());

		string diretorioComprimido;
		diretorioComprimido = "lzw\\compressed_lzw_";
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

		string decompressed_name = "lzw\\decompressed_lzw_";
		decompressed_name.append(directories.getFilenames().at(i).c_str());

		ofstream decompressed_file;
		decompressed_file.open(decompressed_name.c_str());

		for (unsigned int j = 0; j < decompressed.length(); j++)
		{
			decompressed_file << decompressed.at(j);
		}

		decompressed_file.close();
	}

	/* COMPRESSED AND DECOMPRESSED WITH HUFFMAN */
	for (unsigned int i = 0; i < directories.getFilenames().size(); i++)
	{
		string encode = "C:\\Users\\Miguel\\Desktop\\";
		encode.append(directories.getFilenames().at(i));

		string decode = "huff\\compressed_huff_";
		decode.append(directories.getFilenames().at(i));

		FILE * in = fopen(encode.c_str(), "rb");
		FILE * out = fopen(decode.c_str(), "wb");

		memory_encode_file(in, out);

		string dec = "huff\\decompressed_huff_";
		dec.append(directories.getFilenames().at(i));

		FILE * in1 = fopen(decode.c_str(), "rb");
		FILE * out1 = fopen(dec.c_str(), "wb");

		memory_decode_file(in1, out1);

		fclose(in1);
		fclose(in);
		fclose(out);
		fclose(out1);

	}

	return 0;
}

