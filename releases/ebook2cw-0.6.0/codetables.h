/* 
 * ISO 8859-1 and UTF-8 to Morse code mappings 
 * This file is part of ebook2cw and may be used under the same terms.
 * (c) 2008 Fabian Kurz, DJ1YFK 
 *
 *
 * Currently included: ISO 8859-1 complete (all that can somehow be mapped)
 *                     UTF-8: Latin (basic, some extended) and basic Cyrillic 
 *                            alphabet (32 letters).
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
	"-..-.", 		/* \  XXX */
	NULL, 			/* ] */
	NULL, 			/* ^ */
	NULL, 			/* _ */
	".----.", 		/* ` XXX */
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
	".- .",		/* AE */
	"-.-..",	/* ,C */
	"..-..",	/* `E */
	"..-..",	/* 'E */
	".",		/* ^E */
	".",		/* "E */
	"..",		/* `I */
	"..",		/* 'I */
	"..",		/* ^I */
	"..",		/* "I */
	"-..",		/* -D */
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
	"-..",		/* 'thorn' */ 	
	"...--..",	/* sz */ 	
	".--.-",	/* `a */
	".--.-",	/* 'a */
	".-",		/* ^a */
	".-",		/* ~a */
	".-.-",		/* "a */
	".--.-",	/* °a */
	".- .",		/* ae */
	"-.-..",	/* ,c */
	"..-..",	/* `e */
	"..-..",	/* 'e */
	".",		/* ^e */
	".",		/* "e */
	"..",		/* `i */
	"..",		/* 'i */
	"..",		/* ^i */
	"..",		/* "i */
	"-..",		/* -d */
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
	"-..",		/* 'thorn' */ 	
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
	".- .",		/* AE */
	"-.-..",	/* ,C */
	"..-..",	/* `E */
	"..-..",	/* 'E */
	".",		/* ^E */
	".",		/* "E */
	"..",		/* `I */
	"..",		/* 'I */
	"..",		/* ^I */
	"..",		/* "I */
	"-..",		/* -D */
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
	"-..",		/* 'thorn' */ 	
	"...--..",	/* sz */ 	
	".--.-",	/* `a */
	".--.-",	/* 'a */
	".-",		/* ^a */
	".-",		/* ~a */
	".-.-",		/* "a */
	".--.-",	/* °a */
	".- .",		/* ae */
	"-.-..",	/* ,c */
	"..-..",	/* `e */
	"..-..",	/* 'e */
	".",		/* ^e */
	".",		/* "e */
	"..",		/* `i */
	"..",		/* 'i */
	"..",		/* ^i */
	"..",		/* "i */
	"-..",		/* -d */
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
	"-..",		/* 'thorn' */ 	
	"-.--"		/* "y */		/* 255 */
	".-", ".-", ".-", ".-",	".-", ".-", /* 256-261, As with different hats */
	/* 262-269 Cs with different hats */
	"-.-.", "-.-.", "-.-.", "-.-.", "-.-.", "-.-.", "-.-.", "-.-.",
	"-..", "-..", "-..", "-..",		/* 270-273 Ds with different stuff */
	/* 274-283 different Es */
	".", ".", ".", ".", ".", ".", ".", ".", ".", ".",
	/* 284-291 different Gs */
	"--.", "--.", "--.", "--.", "--.", "--.", "--.", "--.",
	/* 292-295 different Hs */
	"....", "....", "....", "....", 
	/* 296-305 different Is */
	"..", "..", "..", "..", "..", "..", "..", "..", "..", "..",
	/* 306-307 IJ ligatures */
	".. .---", ".. .---",
	/* 308-309 Js */
	".---", ".---",
	/* 310-312 Ks */
	"-.-", "-.-",
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
	/* 346-353 Ss */
	"...", "...", "...", "...", "...", "...", "...", "...", 
	/* 354-359 Ts */
	"-", "-", "-", "-", "-", "-",
	/* 360-371 Us */
	"..-", "..-", "..-", "..-", "..-", "..-", "..-", "..-", "..-",
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
	NULL, NULL, NULL, NULL, NULL, 	/* all kind of weird stuff */
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
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  /* 1023 */

	/* 1024-1039, cyrillic nonstandard stuff */
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	
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

	/* 1104 - 1920 not used yet... */
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
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL	/* 1920 */

};




