#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info{
	char name[50];
	int length;
}Info;
int main(){
	int i, j, count = 0;
	char s[] = "data.txt";
	Info peinfo[100];
	FILE *f = fopen(s, "r");
	unsigned char *tmp = (unsigned char*)malloc(sizeof(unsigned char)*1000);
	while(1){
		if (count >= 89) break;
		fscanf(f, "%[^:]s", peinfo[count].name);
		fgetc(f);
		fscanf(f, "%d", &peinfo[count].length);
		fgetc(f);
		fgetc(f);
		count++;
	}
	fclose(f);
	f = fopen("adsmsext.dll", "rb");
	//*****************************DOS HEADER*****************************
	fseek(f, 0, SEEK_SET);
	printf("Signature 0x5A4D: ");
	fread(tmp, sizeof(char), 2, f);
	for(j=0; j<2; j++)
		printf("%c", tmp[j]);
	putchar('\n');
	
	fseek(f, 60, SEEK_SET);
	printf("(0x3C) Pointer to PE Header: ");
	fread(tmp, sizeof(char), 4, f);
	for(j=0; j<4; j++)
		printf("%02x", tmp[j]);
	putchar('\n');

	//*****************************DOS STUB*****************************
	fseek(f, 78, SEEK_SET);
	printf("DOS STUB: ");
	fread(tmp, sizeof(char), 39, f);
	for(j=0; j<39; j++)
		printf("%c", tmp[j]);
	putchar('\n');

	//*****************************########*****************************
	fseek(f, 128, SEEK_SET);
	for(i=0; i<count; i++){
		printf("%s: ", peinfo[i].name);
		fread(tmp, sizeof(char), peinfo[i].length, f);
		for(j=0; j<peinfo[i].length; j++)
			printf("%02x", tmp[j]);
		putchar('\n');
	}
	fclose(f);
	return 0;
}