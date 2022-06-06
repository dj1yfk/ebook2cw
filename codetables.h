/* 
 * ISO 8859-1 and UTF-8 to Morse code mappings 
 * This file is part of ebook2cw and may be used under the same terms (GPL)
 * (C) 2008-2022 Fabian Kurz, DJ5CW
 *
 * Currently included: ISO 8859-1
 *                      - complete (all that can somehow be mapped)
 *                     Unicode: 
 *                      - Latin (basic, some extended) 
 *                      - Cyrillic alphabet (KOI-7 + Serbian, Macedonian.. )
 *                      - Greek
 *                      - Hebrew
 *
 * Any comments, additions or corrections are welcome: fabian@fkurz.net 
 *
 */

const static char *iso8859[] = {
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	" ",			/* space */
	"..--.",		/* ! */
	".-..-.",		/* " */
	NULL,			/* # */
	"...-..-",		/* $ */
	NULL,			/* % */
	". ...",		/* & */
	".----.",		/* ' */
	"-.--.",		/* ( */
	"-.--.-",		/* ) */
	NULL,			/* * */
	".-.-.",		/* + */
	"--..--",		/* , */
	"-....-",		/* - */
	".-.-.-",		/* . */
	"-..-.",		/* / */
	"-----",		/* 0 */
	".----",		/* 1 */
	"..---",		/* 2 */
	"...--",		/* 3 */
	"....-",		/* 4 */
	".....",		/* 5 */
	"-....",		/* 6 */
	"--...",		/* 7 */
	"---..",		/* 8 */
	"----.",		/* 9 */
	"---...",		/* : */
	"-.-.-.",		/* ; */
	NULL,			/* < */
	"-...-",		/* = */
	NULL,			/* < */
	"..--..",		/* ? */
	".--.-.",		/* @ */
	".-",			/* A */
	"-...",			/* B */
	"-.-.",
	"-..",
	".",
	"..-.",
	"--.",
	"....",
	"..",
	".---",
	"-.-",
	".-..",
	"--",
	"-.",
	"---",
	".--.",
	"--.-",
	".-.",
	"...",
	"-",
	"..-",
	"...-",
	".--",
	"-..-",
	"-.--",
	"--..",			/* Z */
	NULL, 			/* [ */
	"-..-.", 		/* \ */
	NULL, 			/* ] */
	NULL, 			/* ^ */
	NULL, 			/* _ */
	".----.", 		/* ` */
	".-",			/* a */
	"-...",			/* b */
	"-.-.",
	"-..",
	".",
	"..-.",
	"--.",
	"....",
	"..",
	".---",
	"-.-",
	".-..",
	"--",
	"-.",
	"---",
	".--.",
	"--.-",
	".-.",
	"...",
	"-",
	"..-",
	"...-",
	".--",
	"-..-",
	"-.--",
	"--..",		/* z */
	NULL,		/* { */
	NULL,		/* | */
	NULL,		/* } */
	NULL,		/* ~ */
	NULL,		/* DEL */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, 
	".-..-.",	/* « (angle quotes, <<, 171) */ 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	".-..-.",	/* » (angle quotes, >>, 187) */ 
	NULL, NULL, NULL, NULL,
	".--.-",	/* `A */
	".--.-",	/* 'A */
	".-",		/* ^A */
	".-",		/* ~A */
	".-.-",		/* "A */
	".--.-",	/* °A */
	".-.-",		/* AE */
	"-.-..",	/* ,C */
	"..-..",	/* `E */
	"..-..",	/* 'E */
	".",		/* ^E */
	".",		/* "E */
	"..",		/* `I */
	"..",		/* 'I */
	"..",		/* ^I */
	"..",		/* "I */
	"..--.",	/* -D */
	"--.--",	/* ~N */
	"---",		/* `O */
	"---",		/* 'O */
	"---",		/* ^O */
	"---",		/* ~O */
	"---.",		/* "O */
	NULL,		/* x */
	"---.",		/* /O */
	"..-",		/* `U */
	"..-",		/* 'U */
	"..-",		/* ^U */
	"..--",		/* "U */
	"-.--",		/* 'Y */
	".--..",	/* 'thorn' */ 	
	"...--..",	/* sz */ 	
	".--.-",	/* `a */
	".--.-",	/* 'a */
	".-",		/* ^a */
	".-",		/* ~a */
	".-.-",		/* "a */
	".--.-",	/* °a */
	".-.-",		/* ae */
	"-.-..",	/* ,c */
	"..-..",	/* `e */
	"..-..",	/* 'e */
	".",		/* ^e */
	".",		/* "e */
	".---.",	/* `i */
	"..",		/* 'i */
	"..",		/* ^i */
	"..",		/* "i */
	"..--.",	/* -d */
	"--.--",	/* ~n */
	"---",		/* `o */
	"---",		/* 'o */
	"---",		/* ^o */
	"---",		/* ~o */
	"---.",		/* "o */
	NULL,		/* ./. */
	"---.",		/* /o */
	"..-",		/* `u */
	"..-",		/* 'u */
	"..-",		/* ^u */
	"..--",		/* "u */
	"-.--",		/* 'y */
	".--..",	/* 'thorn' */ 	
	"-.--"		/* "y */
};

const static char *utf8table[] = {
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* first 128 are identical*/
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* to iso8859, so that */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* will be used instead */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* - 127 */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* control characters ...*/
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* -159 */
	" ", NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, ".-..-.", NULL, NULL, NULL, NULL, /* 171 << */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, ".-..-.", NULL, NULL, NULL, NULL, /* 187 >> */
	/* same as in ISO8859 */
	".--.-",	/* `A */	/* 192 ... */
	".--.-",	/* 'A */
	".-",		/* ^A */
	".-",		/* ~A */
	".-.-",		/* "A */
	".--.-",	/* °A */
	".-.-",		/* AE */
	"-.-..",	/* ,C */
	"..-..",	/* `E */
	"..-..",	/* 'E */
	".",		/* ^E */
	".",		/* "E */
	"..",		/* `I */
	"..",		/* 'I */
	"..",		/* ^I */
	"..",		/* "I */
	"..--.",	/* -D  according to Wikipedia */
	"--.--",	/* ~N */
	"---",		/* `O */
	"---",		/* 'O */
	"---",		/* ^O */
	"---",		/* ~O */
	"---.",		/* "O */
	NULL,		/* x */
	"---.",		/* /O */
	"..-",		/* `U */
	"..-",		/* 'U */
	"..-",		/* ^U */
	"..--",		/* "U */
	"-.--",		/* 'Y */
	".--..",	/* 'thorn', acc to Wikipedia */ 	
	"...--..",	/* sz */ 	
	".--.-",	/* `a */
	".--.-",	/* 'a */
	".-",		/* ^a */
	".-",		/* ~a */
	".-.-",		/* "a */
	".--.-",	/* °a */
	".-.-",		/* ae */
	"-.-..",	/* ,c */
	"..-..",	/* `e */
	"..-..",	/* 'e */
	".",		/* ^e */
	".",		/* "e */
	".---.",	/* `i */
	"..",		/* 'i */
	"..",		/* ^i */
	"..",		/* "i */
	"..--.",	/* -d Wiki */
	"--.--",	/* ~n */
	"---",		/* `o */
	"---",		/* 'o */
	"---",		/* ^o */
	"---",		/* ~o */
	"---.",		/* "o */
	NULL,		/* ./. */
	"---.",		/* /o */
	"..-",		/* `u */
	"..-",		/* 'u */
	"..-",		/* ^u */
	"..--",		/* "u */
	"-.--",		/* 'y */
	".--..",	/* 'thorn' */ 	
	"-.--",		/* "y */		/* 255 */
	".-", ".-", ".-", ".-",	".-", ".-", /* 256-261, As with different hats */
	/* 262-269 Cs with different hats */
	/* 264-265 -.-.. acc. to Wikipedia, Esperanto etc. */
	"-.-.", "-.-.", "-.-..", "-.-..", "-.-.", "-.-.", "-.-.", "-.-.",
	"-..", "-..", "-..", "-..",		/* 270-273 Ds with different stuff */
	/* 274-283 different Es */
	".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
	/* 284-291 different Gs, first 2 according to Wikipedia (Esperanto) */
	"--.-.", "--.-.", "--.", "--.", "--.", "--.", "--.", "--.",
	/* 292-295 different Hs, first two Esperanto (was: -.--. before, but was
	 * changed: "Originale, Hx  estis -.--. sed tio kolizie estas "(" en ITU-T
	 * F.1, do Hx nun prefere estas ----") */
	"----", "----", "....", "....", 
	/* 296-305 different Is */
	"..", "..", "..", "..", "..", "..", "..", "..", "..", "..",
	/* 306-307 IJ ligatures */
	".. .---", ".. .---",
	/* 308-309 Js, from Wikipedia, Esperanto */
	".---.", ".---.",
	/* 310-312 Ks */
	"-.-", "-.-", "-.-",
	/* 313-322 different Ls */
	".-..", ".-..", ".-..", ".-..", ".-..", ".-..", ".-..",
	".-..", ".-..", ".-..",
	/* 323-331 different Ns */
	"-.", "-.", "-.", "-.", "-.", "-.", "-.", "-.", "-.",
	/* 332-337 Os */
	"---", "---", "---", "---", "---", "---",
	/* 338-339 OEs */
	"---.", "---.",
	/* 340-345 Rs */
	".-.", ".-.", ".-.", ".-.", ".-.", ".-.",
	/* 346-353 Ss, Wikipedia */
	"...", "...", "...-.", "...-.", "...", "...", "...", "...", 
	/* 354-359 Ts */
	"-", "-", "-", "-", "-", "-",
	/* 360-371 Us, 364. 365 Esperanto */
	"..-", "..-", "..-", "..-", "..--", "..--", "..-", "..-", "..-",
	"..-", "..-", "..-",
	/* 372-373 Ws */
	".--", ".--",
	/* 374-377 Ys */
	"-.--", "-.--", "-.--",
	/* 377-382 Zs */
	"--..", "--..", "--..", "--..", "--..", "--..",
	/* 383 S */
	"...",
	/* 384-389 Bs */
	"-...", "-...", "-...", "-...", "-...", "-...",
	NULL, NULL, NULL,   	/* all kind of weird stuff */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL,
	/* Standard Greek Alphabet */   
	".-", "-..." , "--.", "-..", ".", "--..", "....", 
	"-.-.", "..", "-.-", ".-..", "--", "-.", "-..-", "---", 
	".--.", ".-.", NULL, "...", "-", "-.--", "..-.", "----", 
	"--.-", ".--", NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL,
	/* Greek Alphabet, small letters */       
	".-", "-..." , "--.", "-..", ".", "--..", "....", 
	"-.-.", "..", "-.-", ".-..", "--", "-.", "-..-", "---", 
	".--.", ".-.", "...", "...", "-", "-.--", "..-.", "----", 
	"--.-", ".--", NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  /* 1023 */

	/* 1024-1039, cyrillic (Serbian, Macedonian, Ukrainian) UC */
	".", ".", "-.. .---", "--. .---", ".", "-.. --..", "..", "..", 
	".---", ".-.. .---", "-. .---", "-.-.", "-.- .---", "..", "..-","-.. --..", 
	
	/* 32 letters of Russian Cyrillic alphabet */
	".-", "-...", ".--",  "--.", "-..", ".", "...-",	/* 1040-1071 */
	"--..", "..",".---", "-.-", ".-..", "--", "-.", 	/* uppercase */
	"---", ".--.", ".-.", "...", "-", "..-", "..-.",    /* cyrillic */
	"....", "-.-.", "---.", "----", "--.-", "-..-",
	"-.--", "-..-", "..-..", "..--", ".-.-",
	".-", "-...", ".--",  "--.", "-..", ".", "...-",	/* 1072-1103 */
	"--..", "..",".---", "-.-", ".-..", "--", "-.", 	/* lowercase */
	"---", ".--.", ".-.", "...", "-", "..-", "..-.",    /* cyrillic */
	"....", "-.-.", "---.", "----", "--.-", "-..-",
	"-.--", "-..-", "..-..", "..--", ".-.-",

	/* 1004-1119, cyrillic (Serbian, Macedonian, Ukrainian) UC */
	".", ".", "-.. .---", "--. .---", ".", "-.. --..", "..", "..", 
	".---", ".-.. .---", "-. .---", "-.-.", "-.- .---", "..", "..-","-.. --..", 
	
	/* 1120 - 1487 to be done... */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	/* 1488-1514 Hebrew according to Wikipedia */
	".-", "-...", "--.", "-..", "---", ".", "--..", "....", 
	"..-", "..", "-.-", "-.-", ".-..", "--", "--", "-.", "-.",
	"-.-.", ".---", ".--.", ".--.", ".--", ".--", "--.-", ".-.", "...", 
	"-", NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	/* Arabic Alphabet, as per Wikipedia. 
	 * Nobody is possibly ever going to use this :-)
	 * 1569-1610
	 */
	".", NULL, NULL, NULL, NULL, NULL, 
	".-", "-...", "-", "-", "-.-.", 
	".---", "....", "---", "-..", "--..", ".-.", "---.", "...", 
	"----", "-..-", "...-", "..-", "-.--", ".-.-", "--.", NULL, 
	NULL, NULL, NULL, NULL, NULL, "..-.", "--.-", "-.-", 
	".-..", "--", "-.", "..-..", ".--", NULL, "..", NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL /* 1920 */

};




