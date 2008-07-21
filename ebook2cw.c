/* 
ebook2cw - converts an ebook to morse mp3s

Copyright (C) 2008  Fabian Kurz, DJ1YFK

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

/* for mkdir, not used on Windows */
#if !__MINGW32__
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#endif

#include "codetables.h"

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#define PCMBUFFER 220500	/* 20 seconds at 11kHz, for one word. plenty.	*/
#define MP3BUFFER 285000    /* abt 1.25*PCMBUFFER + 7200, as recommended	*/

#define ISO8859 0
#define UTF8    1

#define SINE 0
#define SAWTOOTH 1
#define SQUARE 2

lame_global_flags *gfp;


/* Struct CWP to keep all CW parameters */

typedef struct {
	/* CW parameters */
	int wpm, 
		freq, 
		rt, 
		ft, 
		qrq,
		reset, 
		farnsworth, 
		pBT, 
		waveform, 
		original_wpm;
	float ews;	
	/* mp3, buffers */
	int samplerate,
		brate,
		quality;
	int inpcm_size,
		mp3buffer_size,
		ditlen,								/* normal dit length in samples */
		fditlen,							/* farnsworth ditlen in samples */
		maxbytes;
	short int *dit_buf,
			*dah_buf,
			*inpcm;
	unsigned char *mp3buffer;
	/* Chapter splitting */
	char chapterstr[80], 
		 chapterfilename[80];
	/* encoding and mapping */
	int encoding,
		use_isomapping,
		use_utf8mapping;
	char isomapindex[256];		/* contains the chars to be mapped */
	int utf8mapindex[256];		/* for utf8 as decimal code */
	char isomap[256][4]; 		/* by these strings */
	char utf8map[256][8];

	char configfile[1025];

	char id3_author[80],
		id3_title[80],
		id3_comment[80],
		id3_year[5];

	FILE *outfile;
} CWP;


/* functions */
void init_cw (CWP *cw);
void help (void);
void showcodes (int i);
void makeword(char * text, CWP *cw);
void closefile (int letter, int chw, CWP *cw);
void openfile (int chapter, CWP *cw);
void buf_check (int j, CWP *cw);
void command (char * cmd, CWP *cw);
void readconfig (CWP *cw);
void setparameter (char p, char * value, CWP *cw);
void loadmapping(char *filename, int enc, CWP *cw);
char *mapstring (char *string, CWP *cw);

/* main */

int main (int argc, char** argv) {
	int pos, i;
	int c;
 	char word[1024]="";				/* will be cut when > 1024 chars long */
	int chapter = 0;
	int chw = 0, tw = 0, qw = 0;	/* chapter words, total words, qrq words */
	FILE *infile;

	/* initializing the CW parameter struct with standard values */
	CWP cw;
	cw.wpm = 25;
	cw.freq = 600;
	cw.rt = 50;
	cw.ft = 50;
	cw.qrq = 0;
	cw.reset = 1;
	cw.farnsworth = 0;
	cw.ews = 0.0;
	cw.pBT = 1;
	cw.waveform = SINE;

	cw.samplerate = 11025;
	cw.brate = 16;
	cw.quality = 5;
	
	cw.inpcm_size = PCMBUFFER;
	cw.mp3buffer_size = MP3BUFFER;
	cw.ditlen = 0;
	strcpy(cw.chapterstr, "CHAPTER");
	strcpy(cw.chapterfilename, "Chapter");

	cw.encoding = ISO8859;
	cw.use_isomapping = cw.use_utf8mapping = 0;

	strcpy(cw.configfile, "ebook2cw.conf");

	strcpy(cw.id3_author, "CW audio book");
	strcpy(cw.id3_title, "");
	strcpy(cw.id3_comment, "");
	strcpy(cw.id3_year, "");

	infile = stdin;

	printf("ebook2cw %s - (c) 2008 by Fabian Kurz, DJ1YFK\n\n", VERSION);

	/* 
	 * Find and read ebook2cw.conf 
	 */

	readconfig(&cw);

	while((i=getopt(argc,argv, "o:w:W:e:f:uc:k:Q:R:pF:s:b:q:a:t:y:S:hnT:"))!= -1){
		setparameter(i, optarg, &cw);
	} /* while */

	if (optind < argc) {		/* something left? if so, use as infile */
		if ((argv[optind][0] != '-') && (argv[optind][0] != '\0')) {
			if ((infile = fopen(argv[optind], "r")) == NULL) {
				fprintf(stderr, "Error: Cannot open file %s. Exit.\n", 
								argv[optind]);
				exit(EXIT_FAILURE);
			}
		}
	}

	/* init lame */
	gfp = lame_init();
	lame_set_num_channels(gfp,1);
	lame_set_in_samplerate(gfp, cw.samplerate);
	lame_set_brate(gfp, cw.brate);
	lame_set_mode(gfp,1);
	lame_set_quality(gfp, cw.quality); 
	
	if (lame_init_params(gfp) < 0) {
		fprintf(stderr, "Failed: lame_init_params(gfp) \n");
		return(1);
	}

	/* init pcm_buf and mp3_buf */

	if ((cw.inpcm = calloc(PCMBUFFER, sizeof(short int))) == NULL) {
		fprintf(stderr, "Error: Can't allocate inpcm[%d]!\n", PCMBUFFER);
		exit(EXIT_FAILURE);
	}
	else {
		cw.inpcm_size = PCMBUFFER;
	}

	if ((cw.mp3buffer = calloc(MP3BUFFER, sizeof(unsigned char))) == NULL) {
		fprintf(stderr, "Error: Can't allocate mp3buffer[%d]!\n", MP3BUFFER);
		exit(EXIT_FAILURE);
	}
	else {
		cw.mp3buffer_size = MP3BUFFER;
	}

	printf("Speed: %dwpm, Freq: %dHz, Chapter: >%s<, Encoding: %s\n", cw.wpm, 
		cw.freq, cw.chapterstr, cw.encoding == UTF8 ? "UTF-8" : "ISO 8859-1");

	printf("Effective speed: %dwpm, ", cw.farnsworth ? cw.farnsworth : cw.wpm);
	printf("Extra word spaces: %1.1f, ", cw.ews);
	printf("QRQ: %dmin, reset QRQ: %s\n\n", cw.qrq, cw.reset ? "yes" : "no");

	init_cw(&cw);	/* generate raw dit, dah */

	strcat(cw.chapterstr, " ");

	/* read STDIN, assemble full words (anything ending in ' ') to 'word' and
	 * generate CW, write to file by 'makeword'. words with > 1024 characters
	 * will be split  */

	cw.original_wpm = cw.wpm;					/* may be changed by QRQing */
	chapter = 0;
	openfile(chapter, &cw);

	pos=0;
	while ((c = getc(infile)) != EOF) {

		if (c == '\r') 			/* DOS linebreaks */
				continue;

		word[pos++] = c;
		
		if ((c == ' ') || (c == '\n') || (pos == 1024)) {
			word[pos] = '\0';
			if (strcmp(cw.chapterstr, word) == 0) {	/* new chapter */
				closefile(chapter, chw, &cw);
				chw = 0;
				chapter++;
		
				if (cw.qrq && cw.reset) {	
					cw.wpm = cw.original_wpm;	
					init_cw(&cw);
					qw = 0;
				}
					
				openfile(chapter, &cw);
			}

			/* check for commands: |f or |w */
			if (word[0] == '|') {
				command(word, &cw);
			}
			else {
				makeword(mapstring(word, &cw), &cw);
				chw++; tw++; qw++;
			}

			word[0] = '\0';
			pos = 0;

			/* Every 'qrq' minutes (qrq*wpm words), speed up 1 WpM */
			if (qw == (cw.qrq*cw.wpm)) {
				cw.wpm += 1;
				init_cw(&cw);
				printf("QRQ: %dwpm\n", cw.wpm);
				qw = 0;
			}

		} /* word */

	} /* eof */

	closefile(chapter, chw, &cw);

	free(cw.mp3buffer);
	free(cw.inpcm);

	/* factor 0.9 due to many 'words' which aren't actually words, like '\n' */
	printf("Total words: %d, total time: %d min\n", tw, (int) ((tw/cw.wpm)*0.9));

	lame_close(gfp);

	return(0);
}





/* init_cw  -  generates a dit and a dah to dit_buf and dah_buf */

void init_cw (CWP *cw) {
	int x, len;
	double val, val1, val2;

	/* calculate farnsworth length samples */
	if (cw->farnsworth) {
		if (cw->farnsworth > cw->wpm) {
			fprintf(stderr, "Error: Effective speed (-e %d) must be lower "
							"than character speed (-w %d)!\n", cw->farnsworth, 
							cw->wpm);
			exit(EXIT_FAILURE);
		}
		cw->fditlen = (int) (6.0*cw->samplerate/(5.0*cw->farnsworth));
	}

	/* dah */
	len = (int) (6.0*cw->samplerate/(5.0*cw->wpm));			/* in samples */

	/* ditlen not set == init_cw has not been called yet */
	if (!cw->ditlen) {
		/* allocate memory for the buffer */
		if ((cw->dah_buf = calloc(3*len, sizeof(short int))) == NULL) {
			fprintf(stderr, "Error: Can't allocate dah_buf[%d]\n", len);
			exit(EXIT_FAILURE);
		}
		if ((cw->dit_buf = calloc(len, sizeof(short int))) == NULL) {
			fprintf(stderr, "Error: Can't allocate dit_buf[%d]\n", len);
			exit(EXIT_FAILURE);
		}
	}

	/* both dah_buf and dit_buf are filled in this loop */
	for (x=0; x < 3*len; x++) {
		switch (cw->waveform) {
			case SINE:
				val = sin(2*M_PI*cw->freq*x/cw->samplerate);
				break;
			case SAWTOOTH:
				val = ((1.0*cw->freq*x/cw->samplerate)-
								floor(1.0*cw->freq*x/cw->samplerate))-0.5;
				break;
			case SQUARE:
				val = ceil(sin(2*M_PI*cw->freq*x/cw->samplerate))-0.5;
				break;
		}

		/* Shaping rising edge, same for dit and dah */
		if (x < cw->rt)
				val *= pow(sin(M_PI*x/(2.0*cw->rt)),2);

		val1 = val2 = val;

		/* Shaping falling edge, dit */
		if (x < len) {
		   if (x > (len-cw->ft)) {
				val1 *= pow((sin(2*M_PI*(x-(len-cw->ft)+cw->ft)/(4*cw->ft))), 2);
			}
			cw->dit_buf[x] = (short int) (val1 * 20000.0);
		}

		/* Shaping falling edge, dah */
		if (x > (3*len-cw->ft)) {
				val2 *= pow((sin(2*M_PI*(x-(3*len-cw->ft)+cw->ft)/(4*cw->ft))), 2);
		}
		cw->dah_buf[x] = (short int) (val2 * 20000.0);
	} /* for */
	

	/* Calculate maximum number of bytes per 'dah' for the PCM stream,
	 * this will be used later to check if the buffer runs full
	 * (10000 margin) */

	if (cw->farnsworth) {
		cw->maxbytes = (int) ((4+7.0*cw->ews)*(cw->fditlen)) + 10000;
	}
	else {	
		cw->maxbytes = (int) ((6+7.0*cw->ews) * len) + 10000;
	}

	printf("f=%d, w=%d, max=%d\n", cw->farnsworth, cw->wpm, cw->maxbytes);

	cw->ditlen = len;

	return;
}





/* makeword  --  converts 'text' to CW by concatenating dit_buf amd dah_bufs,
 * encodes this to MP3 and writes to open filehandle outfile */

void makeword(char * text, CWP *cw) {
 const char *code;				/* CW code as . and - */
 int outbytes;

 int c, i, j, u, w;
 int prosign = 0;
 unsigned char last=0;		/* for utf8 2-byte characters */

 j = 0;						/* position in 'inpcm' buffer */

 for (i = 0; i < strlen(text); i++) {
	c = (unsigned char) text[i];
	code = NULL;

	if (c == '\n') { 				/* Same for UTF8 and ISO8859 */
		if ((strlen(text) == 1) && cw->pBT) 	/* paragraph */
			code = " -...- "; 
		else 
			code = " ";
	}
	else if (c == '<') {				/* prosign on */
		prosign = 1;
		continue;
	}
	else if ((c == '>') && prosign) {	/* prosign off */
		prosign = 0;
		code = "";			/* only inserts letter space */
	}
	else if (cw->encoding == ISO8859) {	
		code = iso8859[c];
	}
	else if (cw->encoding == UTF8) {
		/* Character may be 1-byte ASCII or 2-byte UTF8 */
		if (!(c & 128)) {						/* MSB = 0 -> 7bit ASCII */
			code = iso8859[c];					/* subset of iso8859 */
		}
		else {
			if (last && (c < 192) ) {			/* this is the 2nd byte */
				/* 110yyyyy 10zzzzzz -> 00000yyy yyzzzzzz */
				c = ((last & 31) << 6) | (c & 63);
				code = utf8table[c];
				last = 0;
			}
			else {								/* this is the first byte */
				last = c;
			}
		}
	}

	if (last) continue;				/* first of two-byte character read */

	/* Not found anything ... */
	if (code == NULL) {
		code = " ";
		if (c < 255) {
			fprintf(stderr, "Warning: don't know CW for '%c'\n", c);
		}
		else {
			fprintf(stderr, "Warning: don't know CW for unicode &#%d;\n", c);
		}

	}

	/* code contains letter as ./-, now assemble pcm buffer */

	for (w = 0; w < strlen(code) ; w++) {
	
		/* make sure the inpcm buffer doesn't run full,
		 * with a conservative margin. reallocate memory if neccesary */

		buf_check(j, cw);

		c = code[w];

		if (c == '.') 
			for (u=0; u < cw->ditlen; u++)
					cw->inpcm[++j] = cw->dit_buf[u]; 
		else if (c == '-') 
			for (u=0; u < (3*cw->ditlen); u++)
					cw->inpcm[++j] = cw->dah_buf[u]; 
		else 								/* word space */
			for (u=0;u < (int)(1+7*cw->ews)*(cw->farnsworth ? cw->fditlen : cw->ditlen); u++)
					cw->inpcm[++j] = 0; 
	
		for (u=0; u < cw->ditlen; u++)	/* space of one dit length */
				cw->inpcm[++j] = 0; 
	}	/* foreach dot/dash */

	if (prosign == 0) {
		for (u=0; u < (cw->farnsworth ? 3*cw->fditlen - cw->ditlen : 2*cw->ditlen); u++)
			cw->inpcm[++j] = 0; 
	}

 }	/* foreach letter */

 /* j = total length of samples in 'inpcm' */
 
 outbytes = lame_encode_buffer(gfp, cw->inpcm, cw->inpcm, j, cw->mp3buffer, cw->mp3buffer_size);
 if (outbytes < 0) {
	fprintf(stderr, "Error: lame_encode_buffer returned %d. Exit.\n", outbytes);
	exit(EXIT_FAILURE);
 }

 if (fwrite(cw->mp3buffer, sizeof(char), outbytes, cw->outfile) != outbytes) {
	fprintf(stderr, "Error: Writing %db to file failed. Exit.\n", outbytes);
	exit(EXIT_FAILURE);
 }

}


/* closefile -- finishes writing the current file, flushes the encoder buffer */

void closefile (int letter, int chw, CWP *cw) {
 int outbytes;
 char mp3filename[80] = "";

 printf("words: %d, minutes: %d\n", chw, (int) ((chw/cw->wpm)*0.9));

 snprintf(mp3filename, 80, "%s%04d.mp3",  cw->chapterfilename, letter);
 printf("Finishing %s\n\n",  mp3filename);

 outbytes = lame_encode_flush(gfp, cw->mp3buffer, cw->mp3buffer_size);
 
 if (outbytes < 0) {
	fprintf(stderr, "Error: lame_encode_buffer returned %d.\n", outbytes);
	exit(EXIT_FAILURE);
 }

 if (fwrite(cw->mp3buffer, sizeof(char), outbytes, cw->outfile) != outbytes) {
	fprintf(stderr, "Error: Writing %db to file failed. Exit.\n", outbytes);
	exit(EXIT_FAILURE);
 }

 fclose(cw->outfile);
}





/* openfile -- starts a new chapter by opening a new file as outfile */

void openfile (int chapter, CWP *cw) {
	char mp3filename[80] = "";
	static char tmp[80] = "";

	snprintf(mp3filename, 80, "%s%04d.mp3",  cw->chapterfilename, chapter);
	printf("Starting %s\n",  mp3filename);
 
	if ((cw->outfile = fopen(mp3filename, "wb")) == NULL) {
		fprintf(stderr, "Error: Failed to open %s\n", mp3filename);
		exit(EXIT_FAILURE);
	}

	snprintf(tmp, 79, "%s - %d", cw->id3_title, chapter);	/* generate title */

	id3tag_init(gfp);
	id3tag_set_artist(gfp, cw->id3_author);
	id3tag_set_year(gfp, cw->id3_year);
	id3tag_set_title(gfp, tmp);
	id3tag_set_comment(gfp, cw->id3_comment);

}


void help (void) {
	printf("ebook2cw v%s - (c) 2008 by Fabian Kurz, DJ1YFK, http://fkurz.net/\n", VERSION);
	printf("\nThis is free software, and you are welcome to redistribute it\n"); 
	printf("under certain conditions (see COPYING).\n");
	printf("\n");
	printf("ebook2cw [-w wpm] [-f freq] [-R risetime] [-F falltime]\n");
	printf("         [-s samplerate] [-b mp3bitrate] [-q mp3quality] [-p]\n");
	printf("         [-c chapter-separator] [-o outfile-name] [-Q minutes]\n");
	printf("         [-a author] [-t title] [-k comment] [-y year]\n");
	printf("         [-u] [-S ISO|UTF] [-n] [-e eff.wpm] [-W space]\n");
	printf("	     [infile]\n\n");
	printf("defaults: 25 WpM, 600Hz, RT=FT=50, s=11025Hz, b=16kbps,\n");
	printf("          c=\"CHAPTER\", o=\"Chapter\" infile = stdin\n");
	printf("\n");
	exit(EXIT_SUCCESS);
}


/*  
 *  showcodes
 *  Generates a HTML table of the available CW symbols in codetables.h
 *	i = 1 -> ISO 8859-1, i=0 -> UTF-8
 */

void showcodes (int i) {
	int k;
	int n = i ? 256 : 1921;

	printf("<html><head><META HTTP-EQUIV=\"CONTENT-TYPE\" CONTENT=\"text/html;"
		 	"charset=%s\"></head>\n", i ? "iso-8859-1" : "utf-8");
	printf("<body><h1>ebook2cw codetables.h</h1>\n");
	printf("<h2>%s</h2><table border=\"1\">\n", i ? "ISO 8859-1" : "UTF-8");
	printf("<tr><th>Decimal</th><th>Symbol</th><th>CW</th></tr>\n");

	for (k=0; k < n; k++) {
		printf("<tr>");

		if ((k < 128+i*128) && (iso8859[k] != NULL)) {
			printf("<td>%d</td><td>&#%d;</td><td>%s</td>", k, k, iso8859[k]); 
		}
		else if (utf8table[k] != NULL) {
			printf("<td>%d</td><td>&#%d;</td><td>%s</td>", k, k, utf8table[k]); 
		}
		else {
			printf("<td>%d</td><td>&#%d;</td><td>&nbsp;</td>", k, k); 
		}
	
		printf("</tr>\n");
	}
	
	printf("</table></body></html>\n");

	exit(EXIT_SUCCESS);
}



/* make sure the inpcm-buffer doesn't run full.
 * have to consider the effects of Farnsworth and extra word spacing */

void buf_check (int j, CWP *cw) {

	if (j > cw->inpcm_size - cw->maxbytes) {
			cw->inpcm_size +=  cw->maxbytes;
			cw->mp3buffer_size +=  (int) (1.25 * cw->maxbytes + 7200.0);
			if ((cw->inpcm = realloc(cw->inpcm, cw->inpcm_size*sizeof(short int)))== NULL) {
				fprintf(stderr, "Error: Can't realloc inpcm[%d]\n", cw->inpcm_size);
				exit(EXIT_FAILURE);
			}
			
			if ((cw->mp3buffer = realloc(cw->mp3buffer, cw->mp3buffer_size*sizeof(char))) 
						   	== NULL) {
				fprintf(stderr, "Error: Can't realloc mp3buffer[%d]\n", 
								cw->mp3buffer_size);
				exit(EXIT_FAILURE);
			}
		}

}

/* command
 * Receives a 'word' which starts with a | and then (possibly) a command,
 * to change speed or tone freq.
 */

void command (char * cmd, CWP *cw) {

	int i = 0;
	unsigned char c = 0;

	sscanf(cmd, "|%c%d", &c, &i);

	switch (c) {
		case 'f':
			if ((i > 100) && (i < (int) cw->samplerate/2)) {
				cw->freq = i;
				init_cw(cw);
			}
			else 
				fprintf(stderr, "Invalid frequency: %s. Ignored.\n", cmd);
			break;
		case 'w':
			if (i > 1) {
				cw->wpm = i;
				init_cw(cw);
			}
			else 
				fprintf(stderr, "Invalid speed: %s. Ignored.\n", cmd);
			break;
		case 'e':
			if (i > 1) {
				cw->farnsworth = i;
				init_cw(cw);
			}
			else 
				fprintf(stderr, "Invalid speed: %s. Ignored.\n", cmd);
			break;
		case 'T':
			if (i > 0 && i < 3) {
				cw->waveform = i;
				init_cw(cw);
			}
			else 
				fprintf(stderr, "Invalid waveform: %d. Ignored.\n", i);
			break;
		default:
			fprintf(stderr, "Invalid command %s. Ignored.\n", cmd);				
	}
}

/* readconfig
 *
 * reads a ebook2cw.conf file and sets parameters from the [settings]
 * part, then looks for character mappings in the [mappings] part.
 *
 * ebook2cw.conf is first searched in the current directory, then
 * ~/.ebook2cw/ and finally in DESTDIR/share/doc/ebook2cw/examples/
 * and copied to ~/.ebook2cw/ if needed.
 *
 * A sample config `ebook2cw.conf' is included.
 */

void readconfig (CWP *cw) {
	FILE *conf = NULL;
	char tmp[1024] = "";
	char p;					/* parameter */
	char v[80]="";			/* value */
	static char mapfile[1024]="";
	char *homedir = NULL;
	int j=0;

	if ((conf = fopen(cw->configfile, "r")) == NULL) {
		/* ebook2cw.conf not in current directory */
		if ((homedir = getenv("HOME")) == NULL) {	/* no home or Windows */
			return;
		}
#if !__MINGW32__
		/* Linux/Unix: Look for ~/.ebook2cw/ebook2cw.conf */
		snprintf(cw->configfile, 2048, "%s/.ebook2cw/ebook2cw.conf", homedir);
		if ((conf = fopen(cw->configfile, "r")) == NULL) {
			/* Not in ~/.ebook2cw/ either, look for it in
			 * DESTDIR/ebook2cw/examples/ */
			if ((conf = fopen(DESTDIR
				"/share/doc/ebook2cw/examples/ebook2cw.conf","r")) == NULL) {
				/* cannot find ebook2cw.conf anywhere. silently return */
				return;
			}
			else {
				printf("First run. Copying example configuration files to "
					"%s/.ebook2cw/\n\n", homedir);
				snprintf(tmp, 1024, "%s/.ebook2cw/", homedir);
				j = mkdir(tmp, 0777);
				if (j && (errno != EEXIST)) {
					printf("Failed to create %s. Resuming without config.",tmp);
					return;
				}
				/* ~/.ebook2cw/ created. Now copy ebook2cw.conf and map files */
				snprintf(tmp, 1024, "install -m 644 "DESTDIR
					"/share/doc/ebook2cw/examples/ebook2cw.conf %s/.ebook2cw/",
					homedir);
				if (system(tmp)) {
					printf("Failed to create ~/.ebook2cw/ebook2cw.conf. "
									"Resuming without config.");
					return;
				}

				snprintf(tmp, 1024, "install -m 644 "DESTDIR
					"/share/doc/ebook2cw/examples/isomap.txt %s/.ebook2cw/",
					homedir);
				if (system(tmp)) {
					printf("Failed to create ~/.ebook2cw/isomap.txt. "
									"Resuming without config.");
					return;
				}

				snprintf(tmp, 1024, "install -m 644 "DESTDIR
					"/share/doc/ebook2cw/examples/utf8map.txt %s/.ebook2cw/",
					homedir);
				if (system(tmp)) {
					printf("Failed to create ~/.ebook2cw/utf8map.txt. "
									"Resuming without config.");
					return;
				}

				/* Succcess. files installed to ~/.ebook2cw/ */

				snprintf(cw->configfile, 1024, "%s/.ebook2cw/ebook2cw.conf",
								homedir);

				/* open newly installed config file ... */
				if ((conf = fopen(cw->configfile, "r")) == NULL) {
					printf("Couldn't read %s! Continue without config.",
									cw->configfile);
					return;
				}

			}
		}
#endif
	}

	printf("Reading configuration file: %s\n\n", cw->configfile);

	/* We start in the [settings] section.
	 * All settings are ^[a-zA-Z]=.+$ 
	 * */

	while ((feof(conf) == 0) && (fgets(tmp, 80, conf) != NULL)) {
		tmp[strlen(tmp)-1]='\0';
		if (strstr(tmp, "[mappings]")) {		/* all parameters read */
			break;
		}
		else {
			if (sscanf(tmp, "%c=%s", &p, v) == 2) {
				setparameter(p, v, cw);
			}
		}
	}

	/* mappings */


	while ((feof(conf) == 0) && (fgets(tmp, 80, conf) != NULL)) {
		tmp[strlen(tmp)-1]='\0';
		if (sscanf(tmp, "isomapfile=%255s", mapfile) == 1) {
				loadmapping(mapfile, ISO8859, cw);
		}
		else if (sscanf(tmp, "utf8mapfile=%255s", mapfile) == 1) {
				loadmapping(mapfile, UTF8, cw);
		}
	}
}


void setparameter (char i, char *value, CWP *cw) {

		switch (i) {
			case 'w':
				if ((cw->wpm = atoi(value)) < 1) {
					fprintf(stderr, "Error: Speed (-w) must be > 0!\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'f':
				cw->freq = atoi(value);
				break;
			case 'R':
				cw->rt = atoi(value);
				break;
			case 'F':
				cw->ft = atoi(value);
				break;
			case 's':
				cw->samplerate = atoi(value);
				break;
			case 'b':
				cw->brate = atoi(value);
				break;
			case 'q':
				cw->quality = atoi(value);
				break;
			case 'c':
				strncpy(cw->chapterstr, value, 78);
				break;
			case 'o':
				strncpy(cw->chapterfilename, value, 78);
				break;
			case 'a':
				strncpy(cw->id3_author, value, 78);
				break;
			case 't':
				strncpy(cw->id3_title, value, 75);
				break;
			case 'k':
				strncpy(cw->id3_comment, value, 78);
				break;
			case 'y':
				strncpy(cw->id3_year, value, 4);
				break;
			case 'Q':
				if ((cw->qrq = atoi(value)) < 1) {
					fprintf(stderr, "Error: QRQ time (-Q) must be > 0!\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'u':
				cw->encoding = UTF8;
				break;
			case 'S':
				if (strstr(value, "ISO")) {
					showcodes(1);
				}
				else {
					showcodes(0);
				}
				break;
			case 'e':				/* effective speed in WpM */
				if ((cw->farnsworth = atoi(value)) < 1) {
					fprintf(stderr, "Error: Eff. speed (-e) must be > 0!\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'W':
				cw->ews = atof(value);
				break;
			case 'n':
				cw->reset = 0;
				break;
			case 'p':
				cw->pBT = 0;
				break;
			case 'h':
				help();
				break;
			case 'T':
				if (strstr(value, "SINE") || atoi(value) == 1) {
					cw->waveform = SINE;
				}
				else if (strstr(value, "SAWTOOTH") || atoi(value) == 2) {
					cw->waveform = SAWTOOTH;
				}
				else if (strstr(value, "SQUARE") || atoi(value) == 3) {
					cw->waveform = SQUARE;	
				}
				break;
		} /* switch */

}

/* loadmapping
 *
 * opens a mapping file and writes the mappings to the mapping variables:
 * index:     utf8mapindex, isomapindex
 * mappings:  utf8map, isomap
 *
 * */


void loadmapping(char *file, int enc, CWP *cw) {
	FILE *mp;
	char tmp[81] = "";
	int i=0;
	int k=0;
	char c1=0;
	char c2=0;
	char s[6]="";

	if ((mp = fopen(file, "r")) == NULL) {
		fprintf(stderr, "Warning: Unable to open mapping file %s. Ignored.\n", 
								file);
		return;
	}

	switch (enc) {
			case ISO8859:
				memset(cw->isomapindex, 0, sizeof(char)*256);
				cw->use_isomapping = 1;
				break;
			case UTF8:
				memset(cw->utf8mapindex, 0, sizeof(int)*256);
				cw->use_utf8mapping = 1;
				break;
	}


	while ((feof(mp) == 0) && (fgets(tmp, 80, mp) != NULL)) {
		tmp[strlen(tmp)-1]='\0';

		switch (enc) {
			case ISO8859:
				if (sscanf(tmp, "%c=%3s", &c1, s) == 2) {
					cw->isomapindex[i] = c1;
					strncpy(cw->isomap[i], s, 3);
					i++;
				}	
				break;
			case UTF8:
				if (sscanf(tmp, "%c=%5s", &c1, s) == 2) {
						cw->utf8mapindex[i] = c1;
						strncpy(cw->utf8map[i], s, 5);
						i++;
				}
				else if (sscanf(tmp, "%c%c=%5s", &c1, &c2, s) == 3) {
						k = ((c1 & 31) << 6) | (c2 & 63);	/* decimal */
						cw->utf8mapindex[i] = k;			/* unicode char */
						strncpy(cw->utf8map[i], s, 5);
						i++;
				}
				break;
		}

		/* only memory for 256 mappings allocated. never going to happen */
		if (i == 255) {
			fprintf(stderr, "Warning: Maximum number (256) of mappings reached"
							" in %s! Stopped here.", file);
			break;
		}

	} /* while */

}


/* mapstring
 * receives a string and replaces all characters that show up in isomapindex /
 * utf8mapindex with their replacement strings, and returns it.
 */


char *mapstring (char * string, CWP *cw) {
	static char new[2048]="";
	char c;
	int i, j, replaced;
	unsigned char last=0;

	memset(new, 0, 2048);
	
	switch (cw->encoding) {
		case ISO8859:
			if (!cw->use_isomapping) {
				return string;
			}
			while ((c = *string++) != '\0') {
				replaced = 0;
				for (i=0; i < 255; i++) {
					if (cw->isomapindex[i] == 0) {
						break;
					}
					else if (cw->isomapindex[i] == c) {
						strcat(new, cw->isomap[i]);
						replaced = 1;
						break;
					}
				}
				if (!replaced) {
					new[strlen(new)] = c;
				}
			}
		break;
		case UTF8:
			if (!cw->use_utf8mapping) {
				return string;
			}
			while ((c = *string++) != '\0') {
				j = 0;
				replaced = 0;
				if (!last && (c & 128)) {		/* first of a 2 char seq */
					last = c;
					continue;
				}
				if (last) {	
					/* 110yyyyy 10zzzzzz -> 00000yyy yyzzzzzz */
					j = ((last & 31) << 6) | (c & 63);
				}
				else {
					j = c;
				}
				for (i=0; i < 255; i++) {
					if (cw->utf8mapindex[i] == 0) {
						break;
					}
					else if (cw->utf8mapindex[i] == j) {
						strcat(new, cw->utf8map[i]);
						replaced = 1;
						break;
					}
				}
				if (!replaced) {
					if (last) {
						new[strlen(new)] = last;
						new[strlen(new)] = c;
					}
					else {
						new[strlen(new)] = c;
					}
				}
				last = 0;
			}
	}

	return new;

}






