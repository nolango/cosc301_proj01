/*
 *
 * Nolan Gonzalez
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "list.h"

void usage(char *program) {
    fprintf(stderr, "usa	ge: %s [<datafile>]\n", program);
    exit(1);
}


void strip_hash(char* str){
	int i;
	for(; i < strlen(str); i++){
		if(str[i] == '#'){
			str[i] = '\0';
		}
	}
	return;
}

int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:	
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
	struct node *head = NULL;
	struct node **list = &head;
	/* read in file */
	char *current_num = (char*)malloc(128);
	int i = 0;
	int j = 0;
	int num;
	int isInt = 1;

	// for each line: tokenify, check if each token is int, add
	while(fgets(current_num,128,datafile) != NULL) {
		// remove comments
		strip_hash(current_num);
		char *token = strtok(current_num, " \n\t");
		if(token == NULL) 
			continue;

		char* tokencpy;
		// for each token in line
		for(;token != NULL; token = strtok(NULL, " \n\t")){
			tokencpy = strdup(token);

			// ignore first char if it's a neg. symbol
			if(token[0] == '-') j = 1;

			// for each char in token
			for(; j < strlen(token); j++){
				if(!isdigit(token[j]) || token[j] == '.')
					isInt = 0;
			}// end for
			j = 0;
			
			// if not int, continue
			if(!isInt){
				isInt = 1;
				continue;
			}

			// token is int, add to list
			i = 0;
			num = atoi(tokencpy);
			sorted_insert(num, list);
		}// end for
	}// end while
	list_print(*list);
    fclose(datafile);

	//printing stats
	struct rusage stats;
	getrusage(RUSAGE_SELF, &stats);
	long user_time = stats.ru_utime.tv_sec;
	long sys_time = stats.ru_stime.tv_sec;

	printf("user time: %ld.%010ld\n", stats.ru_utime.tv_sec,stats.ru_utime.tv_usec);
	printf("system time: %ld.%010ld\n",stats.ru_stime.tv_sec,stats.ru_stime.tv_usec);
    return 0;
}

