#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



void clear_mem(struct Word *);
int btod(char *);
char* dtob(int);
void display_mem();
struct Word* getMainMemory();
void load_file(char *);
void user_code();

const int mem_size = 4096;
const int word_size = 16;

/*
 * Clears the memory by filling it with 0s
 */

void clear_mem(struct Word *main_memory){
	memset (main_memory, 0, mem_size);
}

/* 
* Converts a binary string into a decimal value
*/

int btod(char *binP){
	int dec = 0;
	int counter = 0;
	for(int i = strlen(binP)-1; i >= 0; i--){
		if(binP[i] == '1'){
			dec += pow(2, counter);
		} else if (binP[i] != '0'){
			printf("Error: not a binary number\n");
			return -1;
		}
    counter++;
	}
	return dec;
}

/*
 * Returns a string represtenting a binary number
 */

char* dtob(int dec) {
	static char bin[16];
	bin[0] = '\0';
	int i;
	for (i=word_size-1;i>=0;i--){
		int k = dec >> i;
		if (k & 1){
			strcat(bin, "1");
		} else {
			strcat(bin, "0");
		}
	}
	return bin;
}

void display_mem(){
	int i;
	int temp;
	char bin[16];
	for (i=0;i<=mem_size-1;i++){
		printf("%d\t%s\n", i, dtob(getMainMemory(i)->contents));
	}
}

void user_code(){
	char input[16];
	char exit_string[] = "stop";
	int i = 0;
	while (strcmp(exit_string, input)!=0){
		printf("Please enter the next 16 bit instruction in binary\nEnter 'stop' to stop input: ");
		scanf("%s", input);
		while(((btod(input) == -1) || (strlen(input) > 16)) && (strcmp(exit_string, input)!=0)){
			printf("Enter it again: ");
			scanf("%s", input);
		}
		if (strcmp(exit_string, input)!=0){
			getMainMemory(i)->contents = btod(input);
		}
		i++;
	}
}

void load_file(char *file_name){
	FILE *fp;
	fp = fopen(file_name, "r");
	if(fp == NULL) {
		perror("Error opening file");
		return;
	}
	char temp[16];
	int i = 0;
	while (fgets(temp, 17, fp)!=NULL){
		getMainMemory(i)->contents = btod(temp);
		i++;
	}
	
	
	fclose(fp);
}