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
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
	readDir directories;
	string arg2(argv[2]);
	clock_t start_d;
	start_d = clock();
	if (directories.readDirectories(argv[2]) != 0)
	{
		return 1;
	}
	clock_t end_d;
	end_d = clock();
	cout << "Time elapsed reading the directory: " << (double)(end_d-start_d)/CLOCKS_PER_SEC << endl;
	clock_t start;
	start = clock();

	if (strcmp(argv[1],"-lzw") == 0)
	{
		/* COMPRESS AND DECOMPRESS WITH LZW*/
		for (unsigned int i = 0; i < directories.getFilenames().size(); i++)
		{
			vector<int> compressed;

			string diretorioUtilizado;
			diretorioUtilizado = arg2;
			diretorioUtilizado.append("\\");
			diretorioUtilizado.append(directories.getFilenames().at(i).c_str());

			string diretorioComprimido;
			diretorioComprimido = "lzw\\compressed_lzw_";
			diretorioComprimido.append(directories.getFilenames().at(i).c_str());

			ifstream temp;
			temp.open(diretorioUtilizado.c_str(), ios::binary);
			if (!(temp.is_open()))
			{
				cout << "Erro a abrir o diretório introduzido pelo utilizador" << endl;
				return 2;
			}

			ofstream file;
			file.open(diretorioComprimido.c_str(), ios::binary);
			if (!(file.is_open()))
			{
				cout << "Erro a abrir o diretório onde irão ser gravados os ficheiros" << endl;
				return 3;
			}

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
			if (!(decompressed_file.is_open()))
			{
				cout << "Erro a abrir o diretório onde irão ser gravados os ficheiros" << endl;
				return 4;
			}

			for (unsigned int j = 0; j < decompressed.length(); j++)
			{
				decompressed_file << decompressed.at(j);
			}

			decompressed_file.close();
		}

		clock_t end;
		end = clock();
		cout << "Time elapsed doing lzw: " << (double)(end-start)/CLOCKS_PER_SEC;
	}

	else if (strcmp(argv[1],"-huff")==0)
	{
		clock_t start;
		start = clock();
		/* COMPRESSED AND DECOMPRESSED WITH HUFFMAN */
		for (unsigned int i = 0; i < directories.getFilenames().size(); i++)
		{
			string encode = arg2;
			encode.append("\\");
			encode.append(directories.getFilenames().at(i));

			string decode = "huff\\compressed_huff_";
			decode.append(directories.getFilenames().at(i));

			FILE * in = fopen(encode.c_str(), "rb");
			if (in == NULL)
			{
				cout << "Erro a abrir os ficheiros do diretório introduzidos pelo utilizador" << endl;
				return 5;
			}
			FILE * out = fopen(decode.c_str(), "wb");
			if (out == NULL)
			{
				cout << "Erro a abrir os ficheiros que irão ser gravados" << endl;
				return 6;
			}

			memory_encode_file(in, out);

			string dec = "huff\\decompressed_huff_";
			dec.append(directories.getFilenames().at(i));

			FILE * in1 = fopen(decode.c_str(), "rb");
			if (in1 == NULL)
			{
				cout << "Erro a abrir os ficheiros que irão ser gravados" << endl;
				return 7;
			}
			FILE * out1 = fopen(dec.c_str(), "wb");
			if (out1 == NULL)
			{
				cout << "Erro a abrir os ficheiros que irão ser gravados" << endl;
				return 8;
			}

			memory_decode_file(in1, out1);

			fclose(in1);
			fclose(in);
			fclose(out);
			fclose(out1);

			clock_t end;
			end = clock();
			cout << "Time elapsed doing hzw: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
		}
	}
	return 0;
}

