/*	
 *	base64e.c	
 *
 *			desc.:		This is a simple base64 encode script in pure C
 *					(without external library). Workd with 7bit ASCII.
 *					Attention! It does not check the input string.
 *					Made for WebSocket handshake response, but you can
 *					use it in any project.
 *
 *			usage:		char *msg = "Follow the white rabbit...";
 *					char *enc = base64Encode(msg);
 *
 *			author:		2020 vargalaszlo.com
 *			license:	GPLv3
 *			version:	1.0
 *			
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const unsigned char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char * decToBin(unsigned int num) {
	int i;
	for (i = 0 ; 1 ; i++)
		if (pow(2,i)>num)
			break;
	int bit = ceil((double)i/8)*8;
	char *out = (char *)malloc(bit*sizeof(char));
	for (i = bit-1 ; i >= 0 ; i--, num /= 2)
		out[i]= (num > 0) ? ((num%2) ? '1' : '0') : '0';
	out[bit] = '\0';
	return out;
}

int binToDec(const char * bin) {
	int i, dec = 0;
	for (i = strlen(bin) - 1 ; i >= 0 ; i--)
		dec += pow(2, (strlen(bin)-1)-i)*((int)bin[i] < 49 ? 0 : 1);
	return dec;
}

char * base64Encode(char * msg) {
	int len = strlen(msg);
	int pad = (len%3 != 0) ? 3 - (len%3) : 0;
	char *tri = (char *)malloc(24*sizeof(char)+1);
	char *out = (char *)malloc(((4*len+2)/3+pad)*sizeof(char)+1);
	int i, j, k = 0, l;
	for (i = 0 ; i < len ; i += 3 ) {
		strcpy(tri, decToBin((int)msg[i]));
		strcat(tri, decToBin((int)msg[i+1]));
		if ((int)msg[i+2]>31)
			strcat(tri, decToBin((int)msg[i+2]));
		char arr[6] = {0};
		for (j = 0 ; j < strlen(tri) ; j += 6, k++) {
			strncpy(arr, tri+j, 6);
			if (strlen(arr)%6 != 0)
				for (l =  0 ; l < pad*2 ; l++)
					strcat(arr, "0");
			out[k] = base64_table[binToDec(arr)];
		}	
	}
	for (i = 0 ; i < pad ; i++)
		out[k+i] = '=';
	out[k+i] = '\0';
	return out;
}

int main(int argc, char *argv[]) {
	char *msg = "Follow the white rabbit...";
	char *enc = base64Encode(msg);
	printf ("%s", enc);
	return 0;
}
