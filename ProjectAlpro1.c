#include <stdio.h>
#include <ctype.h>
#include <string.h>
void cipher(char *inp, int pjg){
	int i;
	for (i = 0; i < pjg; i++){
		if (inp[i] > 64 && inp[i] < 91){
			inp[i] = ((inp[i] - 'A' - 3) % 26) + 'A';
			if (inp[i] <= 64){
				inp[i] += 26;
			}
		}
		else if (inp[i] > 96 && inp[i] < 123){
			inp[i] = ((inp[i] - 'a' - 3) % 26) + 'a';
			if (inp[i] <= 96){
				inp[i] += 26;
			}
		}
	}
}
int main(){
	char inp[101];
	printf("Masukkan string yang diinginkan (5 - 100 karakter) : ");
	scanf("%[^\n]", inp);
	getchar();
	int panjang = strlen(inp);
	if (panjang < 5 || panjang > 100){
		printf("String yang dimasukkan tidak memenuhi syarat.\n");
		return 1;
	}
	cipher(inp, panjang);
	printf("String yang telah dienkripsi : %s", inp);
}
