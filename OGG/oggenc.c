#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vorbis/vorbisenc.h>

unsigned int readbuffer[4000]; /* out of the data segment, not the stack */

int main(){
  ogg_stream_state os; /* take physical pages, weld into a logical stream of packets */
  ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
  ogg_packet       op; /* one raw packet of data for decode */
  
  vorbis_info      vi; /* struct that stores all the static vorbis bitstream settings */
  vorbis_comment   vc; /* struct that stores all the user comments */

  vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
  vorbis_block     vb; /* local working space for packet->PCM decode */

  int eos=0,ret;
  int i, founddata;


  vorbis_info_init(&vi);

  ret=vorbis_encode_init_vbr(&vi,1,11025,0.1);

  if(ret) {
		  exit(1);
  }

  vorbis_comment_init(&vc);
  vorbis_comment_add_tag(&vc,"ENCODER","ebook2cw");

  vorbis_analysis_init(&vd, &vi);
  vorbis_block_init(&vd, &vb);
  
  srand(time(NULL));
  ogg_stream_init(&os,rand());

  ogg_packet header;
  ogg_packet header_comm;
  ogg_packet header_code;

  vorbis_analysis_headerout(&vd,&vc,&header,&header_comm,&header_code);
  ogg_stream_packetin(&os,&header); 
  ogg_stream_packetin(&os,&header_comm);
  ogg_stream_packetin(&os,&header_code);

	while (1) {
		int result=ogg_stream_flush(&os,&og);
		if (result==0) break;
		fwrite(og.header,1,og.header_len,stdout);
		fwrite(og.body,1,og.body_len,stdout);
	}

	int onerun=0;
  
  while(!eos){
    long i;
    long bytes = 3800;

	for (i=0; i < 3800; i++) {
		readbuffer[i] = (int) ((sin(i*2.0*3.14*800.0/11025.0)+1)*63.0);
//		fprintf(stderr, "%ld\n", readbuffer[i]);
	}

		//	fread(readbuffer,1,READ*4,stdin); /* stereo hardwired here */

    if(onerun == 100){
		eos=1;
      vorbis_analysis_wrote(&vd,0);
    }else{
	onerun++;

      /* expose the buffer to submit data */
      float **buffer=vorbis_analysis_buffer(&vd,bytes);
    
	  for (i=0; i < bytes; i++) {
			buffer[0][i] = (float) readbuffer[i]/320;
//			fprintf(stderr, "%f\n", buffer[0][i]);
//			buffer[1][i] = readbuffer[i];
	  }

      /* tell the library how much we actually submitted */
      vorbis_analysis_wrote(&vd,i);
    }

    /* vorbis does some data preanalysis, then divvies up blocks for
       more involved (potentially parallel) processing.  Get a single
       block for encoding now */
    while(vorbis_analysis_blockout(&vd,&vb)==1){
//			fprintf(stderr, "anal\n");

      /* analysis, assume we want to use bitrate management */
      vorbis_analysis(&vb,NULL);
      vorbis_bitrate_addblock(&vb);

      while(vorbis_bitrate_flushpacket(&vd,&op)){
	
		/* weld the packet into the bitstream */
		ogg_stream_packetin(&os,&op);
	
		/* write out pages (if any) */
		while(1){
		  int result=ogg_stream_pageout(&os,&og);
		  if(result==0)break;
		  fwrite(og.header,1,og.header_len,stdout);
		  fwrite(og.body,1,og.body_len,stdout);
		  
		  /* this could be set above, but for illustrative purposes, I do
		     it here (to show that vorbis does know where the stream ends) */
		  
		  if(ogg_page_eos(&og)) eos = 1;
		}
      }	/* flushpacket */
    }	/* while blockout */
  }

  /* clean up and exit.  vorbis_info_clear() must be called last */
  
  ogg_stream_clear(&os);
  vorbis_block_clear(&vb);
  vorbis_dsp_clear(&vd);
  vorbis_comment_clear(&vc);
  vorbis_info_clear(&vi);
  
  /* ogg_page and ogg_packet structs always point to storage in
     libvorbis.  They're never freed or manipulated directly */
  
  fprintf(stderr,"Done.\n");
  return(0);
}
