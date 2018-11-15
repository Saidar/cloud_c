#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <time.h>

char * getString(char* input) // number of str
{
	char simbols[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	for(int i = strlen(input); i > -1; i-- )
	{
		if(input[i] == simbols[strlen(simbols) - 1])
		{
			input[i] = simbols[0];
			continue;
			
		};

			for(int j = 0; j < strlen(simbols); j++)
			{
				if(input[i] == simbols[j])
				{
					input[i] = simbols[j + 1]; // shold increase char for next one 
					return input;
				};
			};

	};

	strcat(input, "a"); // do not know how to do with simbols[0]
	return input;
	 
};

int main() {


	FILE *fp; // file stream
	MD5_CTX md5handler; //create md5
	unsigned char md5digest[MD5_DIGEST_LENGTH]; // where to store md5    
	unsigned char output[32]; // out put of md5

	// write part
	fp = fopen("example.txt", "wb"); // open file to stream
	if(fp == NULL) //check if opened or not
	{  
		perror("error open *.txt");
		return EXIT_FAILURE;
	}

	unsigned char line[10]; // input char
	printf("Print line: \n");
	scanf(" %1023[^\n]", line);
	
	unsigned char end[10]; // input char
	printf("Till line: \n");
	scanf(" %1023[^\n]", end);

	char* get = line;

	clock_t begin_t = clock(); // count time	
	int k = 1;
	int j = 0;
	do{
		

		MD5_Init(&md5handler);
		MD5_Update(&md5handler, get, strlen(get));
		MD5_Final(md5digest,&md5handler);	
	   
		for (int i=0;i<MD5_DIGEST_LENGTH;i++) {
			sprintf(&output[i*2], "%02hhx", md5digest[i]);
		};
		strcat(output, "\n");

		
		int count = fputs(get, fp);
		count = fputs(":", fp);
		count = fputs(output, fp);
	
		get = getString(get);
		if(k%1000000 == 0){
			printf("%d\n", j);
			j++;
			k = 0;
		}
		k++;
	}while(strcmp(get,end));
	fclose(fp);

	clock_t end_t = clock();
	double time = (double)(end_t - begin_t) / CLOCKS_PER_SEC;
	printf("%f\n", time);
	printf("%d\n", k);

	return 1;
 
    
};

