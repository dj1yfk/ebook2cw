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

#include "codetables.h"

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#define PCMBUFFER 220500	/* 20 seconds at 11kHz, for one word. plenty.	*/
#define MP3BUFFER 285000    /* abt 1.25*PCMBUFFER + 7200, as recommended	*/

#define ISO8859 0
#define UTF8    1

lame_global_flags *gfp;

FILE *outfile;
FILE *infile;

/* MP3 samplerate, bitrate, quality. */
int samplerate = 11025;
int brate = 16;
int quality = 5;

/* CW parameters */
int wpm = 25;
int freq = 600;
int rt = 50;				/* rise/fall time in samples */
int ft = 50;
int qrq = 0;				/* rise speed by 1 WpM every qrq minutes */
int reset = 1;				/* reset QRQed speed every chapter? */
int farnsworth = 0;			/* farnswoth speed in WpM */
float ews = 0.0;			/* extra word spaces  */ 

/* the buffers for dit, dah, raw pcm and mp3 output, will be calloc'ed to the
 * default values, and -if needed- realloc'ed to the needed size */

short int *dit_buf;
short int *dah_buf;
short int *inpcm;
unsigned char *mp3buffer;

int inpcm_size;
int mp3buffer_size;

int ditlen=0;				/* number of samples in a 'dit' */

/* functions */
int init_cw (int wpm, int freq, int rt, int ft);
void makeword(char * text, int encoding);
void closefile (int letter, int cw);
void buf_check(int j);
void urldecode(char *buf);
int hexit(char c);

/* main */

int main (int argc, char** argv) {
	int pos, i;
	int encoding = ISO8859;
	int c;
 	char word[11000]="";	
 	char text[11000];
	char *querystring;

	outfile = stdout;

	/* init lame */
	gfp = lame_init();
	lame_set_num_channels(gfp,1);
	lame_set_in_samplerate(gfp, samplerate);
	lame_set_brate(gfp, brate);
	lame_set_mode(gfp,1);
	lame_set_quality(gfp, quality); 
	
	if (lame_init_params(gfp) < 0) {
		return(1);
	}

	/* init pcm_buf and mp3_buf */

	if ((inpcm = calloc(PCMBUFFER, sizeof(short int))) == NULL) {
		exit(EXIT_FAILURE);
	}
	else {
		inpcm_size = PCMBUFFER;
	}

	if ((mp3buffer = calloc(MP3BUFFER, sizeof(unsigned char))) == NULL) {
		exit(EXIT_FAILURE);
	}
	else {
		mp3buffer_size = MP3BUFFER;
	}


	printf("Content-type: audio/mpeg\n\n");

	querystring = getenv("QUERY_STRING");

	if (querystring == NULL) {
		exit(1);
	}

	sscanf(querystring, "s=%d&e=%d&f=%d&t=%10000s", &wpm, &farnsworth, &freq, text);

	if ((wpm < 1) || (farnsworth < 1) || (freq < 100)) {
		exit(1);
	}

	if (farnsworth > wpm) {
		farnsworth = wpm;
	}

	strcat(text, " ");

	urldecode(text);

	ditlen = init_cw(wpm, freq, rt, ft);	/* generate raw dit, dah */

	/* read STDIN, assemble full words (anything ending in ' ') to 'word' and
	 * generate CW, write to file by 'makeword'. words with > 1024 characters
	 * will be split  */

	i=0;
	pos=0;
	while ((c = text[i++]) != '\0') {

		word[pos++] = c;
		
		if ((c == ' ') || (c == '\n') || (pos == 1024)) {
			word[pos] = '\0';
			makeword(word, encoding);
			word[0] = '\0';
			pos = 0;
		} /* word */
	} /* eof */

	makeword("            ", encoding);

	free(mp3buffer);
	free(inpcm);

	lame_close(gfp);

	return(0);
}





/* init_cw  -  generates a dit and a dah to dit_buf and dah_buf */

int init_cw (int wpm, int freq, int rt, int ft) {
	int x, len;
	double val;

	/* set farnsworth to samples */
	if (farnsworth) {

		if (farnsworth > wpm) {
			exit(EXIT_FAILURE);
		}


		farnsworth = (int) (6.0*samplerate/(5.0*farnsworth));
	}

	/*	printf("Initializing CW buffers at %d WpM: ", wpm); */

	/* dah */
	len = (int) (3.0*6.0*samplerate/(5.0*wpm));			/* in samples */

	/* ditlen not set == init_cw has not been called yet */
	if (!ditlen) {
		/* allocate memory for the buffer */
		if ((dah_buf = calloc(len, sizeof(short int))) == NULL) {
			exit(EXIT_FAILURE);
		}
	}

	for (x=0; x < len; x++) {
		val = sin(2*M_PI*freq*x/samplerate);
		if (x < rt)  			/* shaping with sin^2 */
				val *= pow(sin(M_PI*x/(2.0*rt)),2);
		
		if (x > (len-ft)) 
				val *= pow((sin(2*M_PI*(x-(len-ft)+ft)/(4*ft))), 2);
		
		dah_buf[x] = (short int) (val * 20000.0);
	}

	/* dit */
	len = (int) (6.0*samplerate/(5.0*wpm));			/* in samples */

	/* ditlen not set == init_cw has not been called yet */
	if (!ditlen) {
		/* allocate memory for the buffer */
		if ((dit_buf = calloc(len, sizeof(short int))) == NULL) {
			exit(EXIT_FAILURE);
		}
	}

	for (x=0; x < len; x++) {
		val = sin(2*M_PI*freq*x/samplerate);
		if (x < rt)  
			val *= pow(sin(M_PI*x/(2.0*rt)), 2); 
		
		if (x > (len-ft)) 
			val *= pow((sin(2*M_PI*(x-(len-ft)+ft)/(4*ft))), 2);
		
		dit_buf[x] = (short int) (val * 20000.0);
	}
	
	return x;		/* = length of dit/silence */
}





/* makeword  --  converts 'text' to CW by concatenating dit_buf amd dah_bufs,
 * encodes this to MP3 and writes to open filehandle outfile */

void makeword(char * text, int encoding) {
 const char *code;				/* CW code as . and - */
 int outbytes;

 int c, i, j, u, w;
 int prosign = 0;

 j = 0;						/* position in 'inpcm' buffer */

 for (i = 0; i < strlen(text); i++) {
	c = (unsigned char) text[i];
	code = NULL;

	if (c == '\n') { 				/* Same for UTF8 and ISO8859 */
		if (strlen(text) == 1) 		/* paragraph */
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
	else if (encoding == ISO8859) {	
		code = iso8859[c];
	}

	/* Not found anything ... */
	if (code == NULL) {
		code = " ";
	}

	/* code contains letter as ./-, now assemble pcm buffer */

	for (w = 0; w < strlen(code) ; w++) {
	
		/* make sure the inpcm buffer doesn't run full,
		 * with a conservative margin. reallocate memory if neccesary */

		buf_check(j);


		c = code[w];

		if (c == '.') 
			for (u=0; u < ditlen; u++)
					inpcm[++j] = dit_buf[u]; 
		else if (c == '-') 
			for (u=0; u < (3*ditlen); u++)
					inpcm[++j] = dah_buf[u]; 
		else 								/* word space */
			for (u=0;u < (int)(1+7*ews)*(farnsworth ? farnsworth : ditlen); u++)
					inpcm[++j] = 0; 
	
		for (u=0; u < ditlen; u++)	/* space of one dit length */
				inpcm[++j] = 0; 
	}	/* foreach dot/dash */

	if (prosign == 0) {
		for (u=0; u < (farnsworth ? 3*farnsworth-ditlen : 2*ditlen); u++)
			inpcm[++j] = 0; 
	}

 }	/* foreach letter */

 /* j = total length of samples in 'inpcm' */
 
 outbytes = lame_encode_buffer(gfp, inpcm, inpcm, j, mp3buffer, mp3buffer_size);
 if (outbytes < 0) {
	exit(EXIT_FAILURE);
 }

 if (fwrite(mp3buffer, sizeof(char), outbytes, outfile) != outbytes) {
	exit(EXIT_FAILURE);
 }

}


/* closefile -- finishes writing the current file, flushes the encoder buffer */

void closefile (int letter, int cw) {
 int outbytes;

 outbytes = lame_encode_flush(gfp, mp3buffer, mp3buffer_size);
 
 if (outbytes < 0) {
	exit(EXIT_FAILURE);
 }

 if (fwrite(mp3buffer, sizeof(char), outbytes, outfile) != outbytes) {
	exit(EXIT_FAILURE);
 }

 fclose(outfile);
}


/* make sure the inpcm-buffer doesn't run full.
 * have to consider the effects of Farnsworth and extra word spacing */

void buf_check (int j) {
	int max;

	/* maximum bytes that may be added for one dot or dah, for either
	 * farnsworth or non-farnsworth */

	max = farnsworth ? (int) ((4+7*ews)*(farnsworth)) : (6+7*ews) * ditlen;
	max += 10000;			/* some margin to feel safe ... */

	if (j > inpcm_size - max) {
			inpcm_size +=  max;
			mp3buffer_size +=  (int) (1.25 * max + 7200.0);
			if ((inpcm = realloc(inpcm, inpcm_size*sizeof(short int)))== NULL) 
						exit(1);
			
			if ((mp3buffer = realloc(mp3buffer, mp3buffer_size*sizeof(char)))
						   	== NULL) 
					exit(1);
		}

}


/* URLDECODE stuff: */

/* Anti-Web HTTPD */
/* Hardcore Software */
/*
This software is Copyright (C) 2001-2004 By Hardcore Software and
others. The software is distributed under the terms of the GNU General
Public License. See the file 'COPYING' for more details.
*/

/*
This code is Copyright (C) 2001 By Zas ( zas at norz.org )
The software is distributed under the terms of the GNU General Public
License. See the file 'COPYING' for more details.
*/

/* I might've modified this slightly, but it's definitley Zas'. -Fractal */

int hexit(char c) {
    if ( c >= '0' && c <= '9' )
        return c - '0';
    if ( c >= 'a' && c <= 'f' )
        return c - 'a' + 10;
    if ( c >= 'A' && c <= 'F' )
        return c - 'A' + 10;
    return 0;
}


/* Decode string %xx -> char (in place) */
void urldecode(char *buf) {
  int v;
  char *p, *s, *w;

  w=p=buf;
  while (*p) {
    v=0;

    if (*p=='%') {
      s=p;
      s++;

      if (isxdigit((int) s[0]) && isxdigit((int) s[1]) ) {
        v=hexit(s[0])*16+hexit(s[1]);
        if (v) { /* do not decode %00 to null char */
          *w=(char)v;
          p=&s[1];
        }
      }

    }

    if (!v) *w=*p;
    p++; w++;
  }
  *w='\0';

  return;

}








