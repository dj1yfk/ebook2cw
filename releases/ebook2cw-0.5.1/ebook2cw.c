/* 
ebook2cw - converts an ebook to morse mp3s

Copyright (C) 2007  Fabian Kurz, DJ1YFK

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA  02110-1301, USA.

source code looks properly indented with tw=4

*/

#include "lame/lame.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#define PCMBUFFER 220500	/* 20 seconds at 11kHz, for one word. plenty.	*/
#define MP3BUFFER 285000    /* abt 1.25*PCMBUFFER + 7200, as recommended	*/

lame_global_flags *gfp;

FILE *outfile;
FILE *infile;

/* MP3 samplerate, bitrate, quality. */
int samplerate = 11025;
int brate = 16;
int quality = 3;

/* CW parameters */
int wpm = 25;
int freq = 600;
int rt = 50;				/* rise/fall time in samples */
int ft = 50;
int qrq = 0;				/* rise speed by 1 WpM every qrq minutes */

/* the buffers for dit, dah, raw pcm and mp3 output, will me calloc'ed to the
 * default values, and if needed realloc'ed to the needed size */

short int *dit_buf;
short int *dah_buf;
short int *inpcm;
unsigned char *mp3buffer;

int inpcm_size;
int mp3buffer_size;

int ditlen=0;				/* number of samples in a 'dit' */

/* Chapters are split by this string */
char chapterstr[80]="CHAPTER";
char chapterfilename[80]="Chapter";		/* full filename: Chapter%02d.mp3 */

/* ID3-tag data: author and title */
char id3_author[80]="CW-Book";
char id3_title[80]="";
char id3_comment[80]="";
char id3_year[5]="";

const static char *codetable[] = {
	".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",".---",
	"-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",
	".--","-..-","-.--","--..","-----",".----","..---","...--","....-",".....",
	"-....", "--...","---..","----."};

/* functions */
int init_cw (int wpm, int freq, int rt, int ft);
void help (void);
void makeword(char * text);
void closefile (int letter, int cw);
void openfile (int chapter);

/* main */

int main (int argc, char** argv) {
	int pos, i, original_wpm;
	char c;
 	char word[1024]="";				/* will be cut when > 1024 chars long */
	int chapter = 0;
	int cw = 0, tw = 0, qw = 0;		/* chapter words, total words, qrq words */

	infile = stdin;

	while((i = getopt(argc, argv, "o:w:f:R:F:s:b:q:c:a:t:k:y:Q:h")) != -1) {
		switch (i) {
			case 'w':
				if ((wpm = atoi(optarg)) < 1) {
					fprintf(stderr, "Error: Speed (-w) must be > 0!\n");
					exit(1);
				}
				break;
			case 'f':
				freq = atoi(optarg);
				break;
			case 'R':
				rt = atoi(optarg);
				break;
			case 'F':
				ft = atoi(optarg);
				break;
			case 's':
				samplerate = atoi(optarg);
				break;
			case 'b':
				brate = atoi(optarg);
				break;
			case 'q':
				quality = atoi(optarg);
				break;
			case 'c':
				strncpy(chapterstr, optarg, 78);
				break;
			case 'o':
				strncpy(chapterfilename, optarg, 78);
				break;
			case 'a':
				strncpy(id3_author, optarg, 78);
				break;
			case 't':
				strncpy(id3_title, optarg, 75);
				break;
			case 'k':
				strncpy(id3_comment, optarg, 78);
				break;
			case 'y':
				strncpy(id3_year, optarg, 4);
				break;
			case 'Q':
				if ((qrq = atoi(optarg)) < 1) {
					fprintf(stderr, "Error: QRQ time (-Q) must be > 0!\n");
					exit(1);
				}
				break;
			case 'h':
			default:
				help();
		} /* switch */
	} /* while */

	if (optind < argc) {		/* something left? if so, use as infile */
		if ((argv[optind][0] != '-') && (argv[optind][0] != '\0')) {
			if ((infile = fopen(argv[optind], "r")) == NULL) {
				fprintf(stderr, "Error: Cannot open file %s. Exit.\n", 
								argv[optind]);
				exit(1);
			}
		}
	}

	printf("ebook2cw %s - (c) 2007 by Fabian Kurz, DJ1YFK\n", VERSION);
	printf("Speed: %d WpM, Freq: %dHz, Chapter: >%s<\n", wpm, freq, chapterstr);


	/* init lame */
	gfp = lame_init();
	lame_set_num_channels(gfp,1);
	lame_set_in_samplerate(gfp, samplerate);
	lame_set_brate(gfp, brate);
	lame_set_mode(gfp,1);
	lame_set_quality(gfp, quality); 
	
	if (lame_init_params(gfp) < 0) {
		fprintf(stderr, "Failed: lame_init_params(gfp) \n");
		return(1);
	}
	else {
		printf("Initialized lame; samplerate=%d, bitrate=%d, quality=%d\n",
					samplerate, brate, quality);
	}


	/* init pcm_buf and mp3_buf */

	if ((inpcm = calloc(PCMBUFFER, sizeof(short int))) == NULL) {
		fprintf(stderr, "Error: Can't allocate inpcm[%d]!\n", PCMBUFFER);
		exit(1);
	}
	else {
		inpcm_size = PCMBUFFER;
	}

	if ((mp3buffer = calloc(MP3BUFFER, sizeof(unsigned char))) == NULL) {
		fprintf(stderr, "Error: Can't allocate mp3buffer[%d]!\n", MP3BUFFER);
		exit(1);
	}
	else {
		mp3buffer_size = MP3BUFFER;
	}

	ditlen = init_cw(wpm, freq, rt, ft);	/* generate raw dit, dah, silence */

	strcat(chapterstr, " ");

	/* read STDIN, assemble full words (anything ending in ' ') to 'word' and
	 * generate CW, write to file by 'makeword'. words with > 1024 characters
	 * will be split  */

	original_wpm = wpm;					/* may be changed by QRQing */
	chapter = 0;
	openfile(chapter);

	pos=0;
	while ((c = getc(infile)) != EOF) {

			if (c == '\r') {			/* DOS linebreaks */
					continue;
			}

			word[pos++] = c;
		
			if ((c == ' ') || (c == '\n') || (pos == 1024)) {
				word[pos] = '\0';
				if (strcmp(chapterstr, word) == 0) {	/* new chapter */
					closefile(chapter, cw);
					cw=0;
					chapter++;
				
					if (qrq) {	
						wpm = original_wpm;					/* restore CW */
						ditlen = init_cw(wpm, freq, rt, ft);
					}
					
					openfile(chapter);
				}
				makeword(word);
				cw++; tw++; qw++;

				word[0] = '\0';
				pos = 0;

				/* every 'qrq' minutes (qrq*wpm words), speed up 1 WpM */
				if (qw == (qrq*wpm)) {
					wpm += 1;
					ditlen = init_cw(wpm, freq, rt, ft);
					qw = 0;
				}
			}



	}
	/* eof */

	closefile(chapter, cw);

	free(mp3buffer);
	free(inpcm);

	/* factor 0.9 due to many 'words' which aren't actually words, like '\n' */
	printf("Total words: %d, total time: %d min\n", tw, (int) ((tw/wpm)*0.9));

	lame_close(gfp);

	return(0);
}





/* init_cw  -  generates a dit and a dah to dit_buf and dah_buf */

int init_cw (int wpm, int freq, int rt, int ft) {
	int x;
	int len;
	double val;

	printf("Initializing CW buffers at %d WpM: ", wpm);

	/* dah */
	len = (int) 3.0*6.0*samplerate/(5.0*wpm);			/* in samples */

	/* ditlen not set == init_cw has not been called yet */
	if (!ditlen) {
		/* allocate memory for the buffer */
		if ((dah_buf = calloc(len, sizeof(short int))) == NULL) {
			fprintf(stderr, "Error: Can't allocate dah_buf[%d]\n", len);
			exit(1);
		}
	}

	for (x=0; x < len; x++) {
		val = sin(2*M_PI*freq*x/samplerate);
		if (x < rt) { 			/* shaping with sin^2 */
				val *= pow(sin(M_PI*x/(2.0*rt)),2);
		}
		if (x > (len-ft)) {
			val *= pow((sin(2*M_PI*(x-(len-ft)+ft)/(4*ft))), 2);
		}

		dah_buf[x] = (int) (val * 20000.0);
	}

	printf("dah_buf[%d], ", x);

	/* dit */
	len = (int) 6.0*samplerate/(5.0*wpm);			/* in samples */

	/* ditlen not set == init_cw has not been called yet */
	if (!ditlen) {
		/* allocate memory for the buffer */
		if ((dit_buf = calloc(len, sizeof(short int))) == NULL) {
			fprintf(stderr, "Error: Can't allocate dit_buf[%d]\n", len);
			exit(1);
		}
	}

	for (x=0; x < len; x++) {
		val = sin(2*M_PI*freq*x/samplerate);
		if (x < rt) { 
			val *= pow(sin(M_PI*x/(2.0*rt)), 2); 
		}
		if (x > (len-ft)) {
			val *= pow((sin(2*M_PI*(x-(len-ft)+ft)/(4*ft))), 2);
		}
		dit_buf[x] = (int) (val * 20000.0);
	}
	
	printf("dit_buf[%d]\n\n", x);

	return x;		/* = length of dit/silence */
}





/* makeword  --  converts 'text' to CW by concatenating dit_buf amd dah_bufs,
 * encodes this to MP3 and writes to open filehandle outfile */

void makeword(char * text) {
 const char *code;				/* CW code as . and - */
 int outbytes;

 int c;
 int i,u,w;
 int j;

 j = 0;			/* position in 'inpcm' buffer */

 for (i = 0; i < strlen(text); i++) {
	c = toupper(text[i]);

	if (c > 64 && c < 91) {			/* trouble with isalpha() under Win32 */
		code = codetable[c-65];		/* even with locale = C ...? */
	}
	else if (c > 47 && c < 58) {
		code = codetable[c-22];
	}
	else if (c == '.') { code = ".-.-.-"; }		/* messy */
	else if (c == ',') { code = "--..--"; }	
	else if (c == '=') { code = "-...-"; } 	
	else if (c == '?') { code = "..--.."; }
	else if (c == '-') { code = "-....-"; }
	else if (c==228 || c==196 || c==-28 || c==-60) { code = ".-.-"; }	/* ae */
	else if (c==252 || c==220 || c==-4 || c==-36) { code = "..--"; }	/* ue */
	else if (c==246 || c==214 || c==-10 || c==-42) { code = "---."; }	/* oe */
	else if (c == 223 || c == -33) { code = "... --.."; }			/* sz */
	else if (c == '(') { code = "-.--."; }
	else if (c == ')') { code = "-.--.-"; }
	else if (c == '!') { code = ".-.-.-"; }	
	else if (c == ';') { code = "-.-.-."; }
	else if (c == '/') { code = "-..-."; }
	else if (c == '@') { code = ".--.-."; }
	else if (c == ':') { code = "---..."; }
	else if (c == '"') { code = ".-..-."; }
	else if (c == '\'') { code = ".----."; }
	else if (c == ' ') { code = " "; }
	else if (c == '\n') { 
		if (strlen(text) == 1) {
				code = " -...- "; 			/* new paragraph */
		}
		else {
				code = " ";
		}
	}
	else {
		code = " ";
		fprintf(stderr, "Warning: don't know CW for '%c'\n", (char) c);
	}

	/* code contains word as ./-, now assemble pcm buffer */

	for (w = 0; w < strlen(code) ; w++) {
	
		/* make sure the inpcm buffer doesn't run full,
		 * with a conservative margin. reallocate memory if neccesary */
		if (j > inpcm_size-(6*ditlen)) {
			inpcm_size +=  (6*ditlen);
			mp3buffer_size +=  (8*ditlen + 7200);
			if ((inpcm = realloc(inpcm, inpcm_size*sizeof(short int)))== NULL) {
				fprintf(stderr, "Error: Can't realloc inpcm[%d]\n", inpcm_size);
			}
			if ((mp3buffer = realloc(mp3buffer, mp3buffer_size*sizeof(char)))
						   	== NULL) {
				fprintf(stderr, "Error: Can't realloc mp3buffer[%d]\n", 
								mp3buffer_size);
			}
		}

		c = code[w];

		if (c == '.') {
			for (u=0; u < ditlen; u++) { inpcm[++j] = dit_buf[u]; }
		}
		else if (c == '-') {
			for (u=0; u < (3*ditlen); u++) { inpcm[++j] = dah_buf[u]; }
		}
		else {
			for (u=0; u < ditlen; u++) { inpcm[++j] = 0; }
		}

		for (u=0; u < ditlen; u++) { inpcm[++j] = 0; }
	
	}

	for (u=0; u < (2*ditlen); u++) { inpcm[++j] = 0; }	/* inter word space */

 }

 /* j = total length of samples in 'inpcm' */
 
 outbytes = lame_encode_buffer(gfp, inpcm, inpcm, j, mp3buffer, mp3buffer_size);
 if (outbytes < 0) {
	fprintf(stderr, "Error: lame_encode_buffer returned %d. Exit.\n", outbytes);
	exit(1);
 }

 if (fwrite(mp3buffer, sizeof(char), outbytes, outfile) != outbytes) {
	fprintf(stderr, "Error: Writing %db to file failed. Exit.\n", outbytes);
	exit(1);
 }

}





/* closefile -- finishes writing the current file, flushes the encoder buffer */

void closefile (int letter, int cw) {
 int outbytes;
 char mp3filename[80] = "";

 printf("words: %d, minutes: %d\n", cw, (int) ((cw/wpm)*0.9));

 sprintf(mp3filename, "%s%02d.mp3",  chapterfilename, letter);
 printf("Finishing %s\n\n",  mp3filename);

 outbytes = lame_encode_flush(gfp, mp3buffer, mp3buffer_size);
 
 if (outbytes < 0) {
	fprintf(stderr, "Error: lame_encode_buffer returned %d.\n", outbytes);
	exit(1);
 }

 if (fwrite(mp3buffer, sizeof(char), outbytes, outfile) != outbytes) {
	fprintf(stderr, "Error: Writing %db to file failed. Exit.\n", outbytes);
	exit(1);
 }

 fclose(outfile);
}





/* openfile -- starts a new chapter by opening Chapter%d.mp3 */

void openfile (int chapter) {
	char mp3filename[80] = "";
	static char tmp[80] = "";

	sprintf(mp3filename, "%s%02d.mp3",  chapterfilename, chapter);
	printf("Starting %s\n",  mp3filename);
 
	if ((outfile = fopen(mp3filename, "wb")) == NULL) {
		fprintf(stderr, "Error: Failed to open %s\n", mp3filename);
		exit(1);
	}

	sprintf(tmp, "%s - %d", id3_title, chapter);	/* generate title */

	id3tag_init(gfp);
	id3tag_set_artist(gfp, id3_author);
	id3tag_set_year(gfp, id3_year);
	id3tag_set_title(gfp, tmp);
	id3tag_set_comment(gfp, id3_comment);

}




void help (void) {
	printf("ebook2cw v%s - (c) 2007 by Fabian Kurz, DJ1YFK, http://fkurz.net/\n", VERSION);
	printf("\n");
	printf("ebook2cw [-w wpm] [-f freq] [-R risetime] [-F falltime]\n");
	printf("         [-s samplerate] [-b mp3bitrate] [-q mp3quality]\n");
	printf("         [-c chapter-separator] [-o outfile-name] [-Q minutes]\n");
	printf("         [-a author] [-t title] [-k comment] [-y year]\n");
	printf("         [infile]\n\n");
	printf("defaults: 25 WpM, 600Hz, RT=FT=50, s=11025Hz, b=16kbps,\n");
	printf("          c=\"CHAPTER\", o=\"Chapter\" infile = stdin\n");
	printf("\n");
	exit(0);
}


