void printInfo(FILE *f, int seek, int length, int mode){
	int j;
	unsigned char *tmp = (unsigned char*)malloc(sizeof(unsigned char)*1000);
	fseek(f, seek, SEEK_SET);
	fread(tmp, sizeof(char), length, f);
	switch(mode){
		case 0: 
			for(j=0; j<strlen(tmp); j++)
				printf("%02x", tmp[j]);
			break;
		case 1:
			for(j=0; j<strlen(tmp); j++)
				printf("%c", tmp[j]);
			break;
	}
}
int main(){
	FILE *f = fopen("ati2erec.dll", "rb");
	printInfo(f, 60, 4, 0);
	fclose(f);

}