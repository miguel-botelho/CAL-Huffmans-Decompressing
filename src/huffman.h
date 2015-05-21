/*
 * huffman.h
 *
 *  Created on: 21/05/2015
 *      Author: Miguel
 */

#ifndef SRC_HUFFMAN_H_
#define SRC_HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <winsock2.h>

int huffman_encode_file(FILE *in, FILE *out);
int huffman_decode_file(FILE *in, FILE *out);
int huffman_encode_memory(const unsigned char *bufin, unsigned int bufinlen, unsigned char **pbufout, unsigned int *pbufoutlen);
int huffman_decode_memory(const unsigned char *bufin, unsigned int bufinlen, unsigned char **bufout, unsigned int *pbufoutlen);



#endif /* SRC_HUFFMAN_H_ */
