/* with help of several classmates, i was able to get the program to work
	but not through fgets (it wouldn't print out to screen) and not through
	a seperate function. all other testing works though */

/* The Libaries */
#include <stdio.h>
#include <string.h>


/* define variables */
#define OUT 0			/* out comment */
#define IN 1			/* in comment */
#define GOING_IN 2
#define GOING_OUT 3
#define QUOTE 4
#define BUF_SIZE 64



/* main function */
int main(int argc, char **argv) {
	char fileNamer[BUF_SIZE];
	int cur;			/* current char */
	int temp; 			/* need a temp for the quote else if */ 
	int lines = 0;		/* line counter */
	int lError = 0;		/* locates line of an error */
	int state = OUT;	/* begins the code in the out state */

		printf("Please enter file name to read, including full file extension: \n");
		//fgets(fileNamer, BUF_SIZE, stdin);
		//strtok(fileNamer, "/n");
		//fileNamer[strlen(fileNamer-1)]='\0';
		scanf("%s", fileNamer);
		FILE *fpr;
		fpr = fopen(fileNamer, "rw");
		if(fpr==NULL){
			printf("Couldn't find file!\n\n");
			return 1;
		}
		
		/* Begins the while loop, to cycle through the files characters */
		while((cur=getc(fpr)) != EOF){

			/* increments new line variable */
			if(cur == '\n')
				lines++;

			/* begins out, checks for backslash */
			if(state == OUT && cur == '/'){
				state = GOING_IN;
				temp = cur;
			}
			/* begins out, checks for either qoutations */
			else if(state == OUT && cur == '\"' || cur == '\''){
				putchar(cur);
				state = QUOTE;
				lError = lines;
			}
			/* moves along */
			else if(state == OUT){
				putchar(cur);
			}
			/* found backslash, checks for astreick */
			else if(state == GOING_IN && cur == '*'){
				state = IN;
				lError = lines;
			}
			/* found backslash, checks for qoutations */
			else if(state == GOING_IN && cur == '\"' || cur == '\''){
				putchar(temp);
				putchar(cur);
				state = QUOTE;
				lError = lines;
			}
			/* found quotation, moving along checking for end quotation */
			else if(state == QUOTE && cur == '\"' || cur == '\''){
				putchar(cur);
				state = OUT;
			}
			/* still in quote, moving along */
			else if(state == QUOTE){
				putchar(cur);
			}
			/* not in, moves along */
			else if(state == GOING_IN){
				putchar(temp);
				putchar(cur);
				state = OUT;
			}
			/* in a comment, but now preparing to leave */
			else if(state == IN && cur == '*'){
				state = GOING_OUT;
				lError = lines;
			}
			/* now in the comment */
			else if(state == IN){
				;
			}
			/* leaving comment, checks for backslash */
			else if(state == GOING_OUT && cur == '/'){
				state = OUT;
			}
			/* no backslash, moving along */
			else if(state == GOING_OUT){
				state = IN;
			}
	}

	/* This starts the error section of the code which i completely forgot
		about. This finds if the code ever close a comment or quote */
	
	/* Checks if the comment was ever closed */
	if(state == IN) {
		printf("Failed to close comment on line: %d", lError);
		return 1;
	} 
	/* Checks if the quote was ever closed */
	else if(state == QUOTE){
		printf("Failed to close Quotation on line: %d", lError);
		return 1;
	}
	/* This tells you that the file was decommented and finished */
	else{
		printf("File finished and decommented!\n");
		return 0;
	}
	fclose(fpr);
}