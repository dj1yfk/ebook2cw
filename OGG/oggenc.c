#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vorbis/vorbisenc.h>

signed int readbuffer[4000]; /* out of the data segment, not the stack */

	ogg_stream_state os; /* take physical pages, weld into a logical stream of packets */
	ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
	ogg_packet       op; /* one raw packet of data for decode */
	vorbis_info      vi; /* struct that stores all the static vorbis bitstream settings */
	vorbis_comment   vc; /* struct that stores all the user comments */
	vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
	vorbis_block     vb; /* local working space for packet->PCM decode */

int main(){
	int i, founddata;
	int result;
	int eos=0,ret;
	int onerun=0;

	srand(time(NULL));

	/* Vorbis Init */

	ogg_packet header;
	ogg_packet header_comm;
	ogg_packet header_code;

	vorbis_info_init(&vi);
	if (vorbis_encode_init_vbr(&vi,1,11025,0.1)) {
		exit(1);
	}

	vorbis_comment_init(&vc);
	vorbis_comment_add_tag(&vc,"ENCODER","ebook2cw");
	vorbis_analysis_init(&vd, &vi);
	vorbis_block_init(&vd, &vb);
	ogg_stream_init(&os,rand());

	vorbis_analysis_headerout(&vd,&vc,&header,&header_comm,&header_code);
	ogg_stream_packetin(&os,&header); 
	ogg_stream_packetin(&os,&header_comm);
	ogg_stream_packetin(&os,&header_code);

	while (ogg_stream_flush(&os,&og)) {
		fwrite(og.header,1,og.header_len,stdout);
		fwrite(og.body,1,og.body_len,stdout);
	}

	/* Vorbis init done */
  
while (!eos) {
    long i;
    long bytes = 3800;

	for (i=0; i < bytes; i++) {
		readbuffer[i] = (int) ((sin(i*2.0*3.14*900.0/11025.0))*63.0);
	}

	fprintf(stderr, "Run %d\n", onerun);


    if (onerun == 20) {
		eos=1;
		vorbis_analysis_wrote(&vd,0);
    }
    else {
		onerun++;

		/* expose the buffer to submit data */
		float **buffer = vorbis_analysis_buffer(&vd,bytes);
	
		for (i=0; i < bytes; i++) {
			buffer[0][i] = (float) readbuffer[i]/200.0;
		}
			vorbis_analysis_wrote(&vd,i);	/* tell how much submitted */
	}

    /* Encode and write */
	while (vorbis_analysis_blockout(&vd,&vb) == 1) {
		vorbis_analysis(&vb,NULL);
		vorbis_bitrate_addblock(&vb);
			while (vorbis_bitrate_flushpacket(&vd,&op)) {
				ogg_stream_packetin(&os,&op);
				while (1) {
					int result = ogg_stream_pageout(&os,&og);
					if (result == 0) break;
					fwrite(og.header,1,og.header_len, stdout);
					fwrite(og.body,1,og.body_len, stdout);
					if(ogg_page_eos(&og)) eos = 1;
				}
			}
	}

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


/* vim: noai:ts=4:sw=4 
 * */

