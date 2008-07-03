#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void help (void);
void openfile (void);

FILE *infile;
FILE *outfile;
FILE *outmain;
int lines;
char o[256];
char os[256];
char name[256];
int part = 0;

int main(int argc, char** argv) {

	int c,l;
	int cutnext = 0;

	if (argc != 4) {
		help();
		return(0);
	}
	else {
		if ((lines = atoi(argv[1])) == 0) {
			fprintf(stderr, "Lines must be > 0\n");
			exit(1);
		}
		if ((infile = fopen(argv[2], "r")) == NULL) {
			fprintf(stderr, "Unable to open %s.\n", argv[2]);
			exit(1);
		}
		strcpy(name, argv[3]);
	}

	openfile();

	sprintf(os, "split-%s", argv[2]);
	if ((outmain = fopen(os, "w")) == NULL) {
		fprintf(stderr, "Error, couldn't open file %s.", o);
		exit(1);
	}

	l = 0;
	while ((c = getc(infile)) != EOF) {

			if (c == '\r') { continue;}

			if (c == '\n') {
				l++;
			}

			if (l > (lines-1)) {
				cutnext = 1;
			}

			putc(c, outfile);
			putc(c, outmain);
			
			if ((c == '.') && cutnext) {
				l = 0;
				cutnext = 0;
				part++;
				openfile();
				fputs("\n ^ \n", outmain);
			}	
	}









}



void help (void) {
	printf("e2csplit - Usage:  e2csplit lines input.txt\n");
}


void openfile (void) {

	if (part != 0) {
		fclose(outfile);
	}

	sprintf(o, "%s-%04d.txt", name, part);
	if ((outfile = fopen(o, "w")) == NULL) {
		fprintf(stderr, "Error, couldn't open file %s.", o);
		exit(1);
	}

}

