/*
 * main.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Miguel
 */

#include "readDir.h"
#include "huffman.h"
#include "huffcoding.cpp"
#include "lzw1.h"
#include <algorithm>
#include <iterator>
#include <bitset>
#include <sstream>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		cout << "Número de argumentos errado." << endl << endl;
		cout << "Usage: -huff/-lzw Diretorio" << endl;
		return -1;
	}

	readDir directories;
	string arg2(argv[2]);
	clock_t start_d = clock();
	if (directories.readDirectories(argv[2]) != 0)
	{
		return 1;
	}
	clock_t end_d = clock();
	cout << "Time elapsed reading the directory: " << (double)(end_d-start_d)/CLOCKS_PER_SEC << endl;

	if (strcmp(argv[1],"-lzw") == 0)
	{
		clock_t start = clock();
		start = clock();
		//COMPRESS AND DECOMPRESS WITH LZW
		for (unsigned int i = 0; i < directories.getFilenames().size(); i++)
		{
			LZWCodec lzw;

			string diretorioUtilizado = "";
			diretorioUtilizado = arg2;
			diretorioUtilizado.append("\\");
			diretorioUtilizado.append(directories.getFilenames().at(i).c_str());

			string diretorioComprimido = "";
			diretorioComprimido = "lzw\\compressed_lzw_";
			diretorioComprimido.append(directories.getFilenames().at(i).c_str());

			FILE *inFile, *outFile, *outFile1;

			string decompressed_name = "lzw\\decompressed_lzw_";
			decompressed_name.append(directories.getFilenames().at(i).c_str());

			inFile = fopen(diretorioUtilizado.c_str(), "rb");
			outFile = fopen(diretorioComprimido.c_str(), "wb");
			outFile1 = fopen(decompressed_name.c_str(), "wb");

			long curPos, endPos;
			curPos = ftell(inFile);
			fseek(inFile, 0, 2);
			endPos = ftell(inFile);
			fseek(inFile, curPos, 0);
			size_t conteudoLength = endPos;

			char *buffer = (char *) malloc(conteudoLength);

			vector<unsigned char> conteudo(conteudoLength);
			vector<unsigned char> decoded;
			vector<unsigned char> encoded;

			fread(&conteudo[0], 1, conteudo.size(), inFile);

			lzw.encode(conteudo, encoded);
			lzw.decode(encoded, decoded);

			fwrite(&encoded[0], 1, encoded.size(), outFile);
			fwrite(&decoded[0], 1, decoded.size(), outFile1);

			fclose(inFile);
			fclose(outFile);
			fclose(outFile1);
			free(buffer);
		}
		clock_t end;
		end = clock();
		cout << "Time elapsed doing lzw: " << (double)(end-start)/CLOCKS_PER_SEC;
	}

	else if (strcmp(argv[1],"-huff")==0)
	{
		clock_t start = clock();
		// COMPRESSED AND DECOMPRESSED WITH HUFFMAN
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
		}
		clock_t end = clock();
		cout << "Time elapsed doing hzw: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
	}
	else
	{
		cout << "Método de compressão selecionado errado. Escolher -lzw ou -huff" << endl;
	}
	return 0;
}

