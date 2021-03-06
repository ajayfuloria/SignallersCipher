#include <stdio.h>
int slookup[16] = {0,8,9,15,12,11,10,3,6,4,1,13,7,14,5,2};
int permuteLookup[32]={6,9,28,12,23,18,1,25,15,16,27,4,31,2,8,21,3,26,7,14,22,11,29,19,10,0,30,17,20,5,24,13};

int invslookup[16] = {0,10,15,7,9,14,8,12,1,2,6,5,4,11,13,3};
int invpermuteLookup[32]={25,6,13,16,11,29,0,18,14,1,24,21,3,31,19,8,9,27,5,23,28,15,20,4,30,7,17,10,2,22,26,12};

int convertStringToNum(char * x){

	unsigned int out[4]= {0,0,0,0},h=0, result;
	char temp;
	for(h = 0; h < 4; h ++){
		temp = x[h];
		out[h] = out[h] | temp;
//		printf("---%d : %02X",h, out[h]);
		out[h] = out[h] << 24;
		out[h] = out[h] >> (8*h);
//		printf("---%d : %02X",h, out[h]);

	}

	result = out[0]|out[1] | out[2]| out[3];
//	printf("---res : %02X",result);

	return result;
}

int convertStringToNumdecrypt(char * x){

	unsigned int out[4]= {0,0,0,0},h=0, result;
	char temp;
	for(h = 0; h < 4; h ++){
		temp = x[h];
		out[h] = out[h] | temp;
//		printf("---%d : %02X",h, out[h]);
		out[h] = out[h] << 24;
		out[h] = out[h] >> (8*h);

//		printf("---%d : %02X",h, out[h]);
		if(out[h] == 255){
			out[h] = 0;
		}
	}

	result = out[0]|out[1] | out[2]| out[3];
//	printf("---res : %02X",result);

	return result;
}
int sBoxLookup(int x){
	int a=0,i;
	
	for(i=0;i<8;i++){
		a+=slookup[(x>>(28-i*4))&15]<<(28-i*4);
	}
	return a;
}
int inversesBoxLookup(int x){
	int a=0,i;

	for(i=0;i<8;i++){
		a+=invslookup[(x>>(28-i*4))&15]<<(28-i*4);
	}
	return a;
}
int per(int x){
	int a=0,i;

	for(i=0;i<32;i++){
		a+=((x>>(31-i))&1)<<(31-permuteLookup[i]);
	}
	
	return a;
}
int inverseper(int x){
	int a=0,i;

	for(i=0;i<32;i++){
		a+=((x>>(31-i))&1)<<(31-invpermuteLookup[i]);
	}

	return a;
}
int roundfunc(int stateVal, int key_round){
		stateVal = sBoxLookup(stateVal);
//		printf("\n The hex value after 1st round Sbox lookup is : %X", stateVal);
//		printf("\n The dec value after 1st round Sbox lookup is : %d", stateVal);
//

		stateVal = per(stateVal);
//		printf("\n hex value after 1st round permutation is : %X", stateVal);
//		printf("\n dec value after 1st round permutation is : %d", stateVal);

		stateVal = stateVal ^ key_round;

	return stateVal;
}
int revroundfunc(int stateVal, int key_round){

		stateVal = stateVal ^ key_round;


		stateVal = inverseper(stateVal);
//		printf("\n hex value after 1st round permutation is : %X", stateVal);
//		printf("\n dec value after 1st round permutation is : %d", stateVal);

		stateVal = inversesBoxLookup(stateVal);
//		printf("\n The hex value after 1st round Sbox lookup is : %X", stateVal);
//		printf("\n The dec value after 1st round Sbox lookup is : %d", stateVal);





	return stateVal;
}
int keyGenerator(int key, int round){

		key += key * 2*round;
		return key;

}
void encrypt(k){
	int key = k;
	//int key = 3517373009;
	char inputBuff[5];
	char ch;
	int x = -1;
	int h = 0;
	int stateVal,index=0;
	char path[50] = {'\0'};
	char newpath[50]= {'\0'};

		char encry[8] = {'e','n','c','r','y','p','t','\0'};
		printf("Enter the file name (with full path) : ");
		fflush(stdout);
		scanf("%s", &path);
		FILE *fr;
		FILE *fw;
		fr = fopen(path, "a+");
		int sz;
				fseek(fr, 0L, SEEK_END);
				sz = ftell(fr);
				if(sz%4 !=0){
					int appendnos = 4-(sz%4);
					for(h = 0; h<appendnos;h++){
						fputc('\0',fr);
					}
				}
				fseek(fr, 0L, SEEK_SET);
				fseek(fr, 0L, SEEK_END);
				sz = ftell(fr);
		for(h = 0; h < 50; h++){
			if(path[h]!='\0'){
				newpath[h] = path[h];
				index = h;
			}
		}
		for(h=0;h<8;h++){
			newpath[index+1+h] = encry[h];
		}
		fw = fopen(newpath, "a+");

		printf("\n Size of file is :: %d",sz);
		fseek(fr, 0L, SEEK_SET);
		while((ch =  getc(fr)) != EOF){ //!feof(fr)) { //
			x+=1;
			//ch = getc(fr);
			inputBuff[x] = ch;
			if(x==3){
			inputBuff[4] = '\0';
			x = -1;
			stateVal = convertStringToNum(inputBuff);
			stateVal = stateVal^key;
			for(h = 1; h < 16; h++){
				int kround = keyGenerator(key, h);
				stateVal = roundfunc(stateVal, kround);
			}
			stateVal = sBoxLookup(stateVal);
			int kround = keyGenerator(key, 16);
			stateVal = stateVal ^ kround;
			char finalWrite[5] ={'\0'};
			for(h=0;h<4;h++){
				int temp = stateVal;
				temp = temp >> (24 - 8*h);
				temp = temp & 255;
				if(temp == 0){
					finalWrite[h] = '\0'; // null
				}else{
					finalWrite[h] = (char)temp;
				}
			}
			fwrite(finalWrite, 1, sizeof(finalWrite)-1, fw);
			}
			}
		fclose(fr);
		fclose(fw);

}

void decrypt(int k){
	//int key = 3517373009;
	int key = k;
	char inputBuff[5];
	char ch;
	int x = -1;
	int h = 0;
	int stateVal,index=0;
	char path[50] = {'\0'};
	char newpath[50]= {'\0'};

		char decry[8] = {'d','e','c','r','y','p','t','\0'};
		printf("Enter the file name (with full path) : ");
		fflush(stdout);
		scanf("%s", &path);
		FILE *fr;
		FILE *fw;

		fr = fopen(path, "r");

		for(h = 0; h < 50; h++){
			if(path[h]!='\0'){
				newpath[h] = path[h];
				index = h;

			}
		}
		for(h=0;h<8;h++){
			newpath[index+1+h] = decry[h];
		}
		fw = fopen(newpath, "w");
		//printf("reached in whikel");
		while(!feof(fr)){ //(ch =  getc(fr)) != EOF){
			x+=1;
			ch =  getc(fr);

			inputBuff[x] = ch;
			if(x==3){
			inputBuff[4] = '\0';

			//printf("%s", inputBuff);

			//printf(": : %02X :: ", inputBuff);
			x = -1;

			stateVal = convertStringToNumdecrypt(inputBuff);
			//printf("\n The hexa for input this is : %X", stateVal);
			//printf("\n %d",stateVal);

			//stateVal = stateVal^key;
			//printf("\n The hex value after key whitening is : %X", stateVal);
		//	printf("\n The dec value after key whitening is : %d",stateVal);

			int kround = keyGenerator(key, 16);
			stateVal = stateVal ^ kround;
			stateVal = inversesBoxLookup(stateVal);


			for(h = 15; h >= 1; h--){
				int kround = keyGenerator(key, h);
				stateVal = revroundfunc(stateVal, kround);
			}

			stateVal = stateVal ^ key;

//			printf("\n The final decyption is hex :  %X", stateVal);
//			printf("\n The final decyption is : %d",stateVal);

			char finalWrite[5] ={'\0'};
			for(h=0;h<4;h++){

				int temp = stateVal;
				temp = temp >> (24 - 8*h);
				temp = temp & 255;
				if(temp == 0){
					finalWrite[h] = '0';
				}else{
					finalWrite[h] = (char)temp;
				}
				//printf("%c",finalWrite[h]);

			}

			fprintf(fw,"%s",finalWrite);
			}

			}
		//printf("%c",out[9]);
		fclose(fr);
		fclose(fw);
}
int main( int argc, char ** argv ) {
	int k;
	char choice = ' ';
	printf("SIGNALLERS CIPHER \n");
	printf("----------------- \n");
	printf("Choose your option\n");
	printf("a. Encrypt a file.\n");
	printf("b. Decrypt a file.\n");
	printf("### : ");
	fflush(stdout);
	scanf("%c",&choice);
	printf("Enter the key : ");
	fflush(stdout);
	scanf("%d",&k);
	switch(choice){

	case 'a' 	:	encrypt(k);

					break;

	case 'b'	:	decrypt(k);
					break;


	default	:	printf("Wrong choice !!! Try again...");
				break;
	}
	return 0;
}
