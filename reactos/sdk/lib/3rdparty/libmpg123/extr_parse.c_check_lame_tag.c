#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {scalar_t__* level; float* gain; scalar_t__* peak; } ;
struct TYPE_8__ {int filelen; } ;
struct TYPE_11__ {int stereo; int framesize; char* bsbuf; scalar_t__ vbr; scalar_t__ audio_start; int abr_rate; int** bsspace; size_t bsnum; scalar_t__ track_frames; TYPE_3__ p; TYPE_2__ rva; TYPE_1__ rdat; scalar_t__ lsf; } ;
typedef  TYPE_4__ mpg123_handle ;

/* Variables and functions */
 scalar_t__ MPG123_ABR ; 
 scalar_t__ MPG123_CBR ; 
 int MPG123_GAPLESS ; 
 int MPG123_IGNORE_INFOFRAME ; 
 int MPG123_IGNORE_STREAMLENGTH ; 
 void* MPG123_VBR ; 
 scalar_t__ NOQUIET ; 
 unsigned long TRACK_MAX_FRAMES ; 
 scalar_t__ VERBOSE2 ; 
 scalar_t__ VERBOSE3 ; 
 unsigned long bit_read_long (char*,int*) ; 
 int bit_read_short (int*,int*) ; 
 int /*<<< orphan*/  check_bytes_left (int) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug1 (char*,unsigned long) ; 
 int /*<<< orphan*/  debug3 (char*,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  frame_fill_toc (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  frame_gapless_init (TYPE_4__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int check_lame_tag(mpg123_handle *fr)
{
	int i;
	unsigned long xing_flags;
	unsigned long long_tmp;
	/*
		going to look for Xing or Info at some position after the header
		                                   MPEG 1  MPEG 2/2.5 (LSF)
		Stereo, Joint Stereo, Dual Channel  32      17
		Mono                                17       9
	*/
	int lame_offset = (fr->stereo == 2)
	? (fr->lsf ? 17 : 32)
	: (fr->lsf ? 9  : 17);

	if(fr->p.flags & MPG123_IGNORE_INFOFRAME) goto check_lame_tag_no;

	debug("do we have lame tag?");
	/*
		Note: CRC or not, that does not matter here.
		But, there is any combination of Xing flags in the wild. There are headers
		without the search index table! I cannot assume a reasonable minimal size
		for the actual data, have to check if each byte of information is present.
		But: 4 B Info/Xing + 4 B flags is bare minimum.
	*/
	if(fr->framesize < lame_offset+8) goto check_lame_tag_no;

	/* only search for tag when all zero before it (apart from checksum) */
	for(i=2; i < lame_offset; ++i) if(fr->bsbuf[i] != 0) goto check_lame_tag_no;

	debug("possibly...");
	if
	(
		   (fr->bsbuf[lame_offset]   == 'I')
		&& (fr->bsbuf[lame_offset+1] == 'n')
		&& (fr->bsbuf[lame_offset+2] == 'f')
		&& (fr->bsbuf[lame_offset+3] == 'o')
	)
	{
		/* We still have to see what there is */
	}
	else if
	(
		   (fr->bsbuf[lame_offset]   == 'X')
		&& (fr->bsbuf[lame_offset+1] == 'i')
		&& (fr->bsbuf[lame_offset+2] == 'n')
		&& (fr->bsbuf[lame_offset+3] == 'g')
	)
	{
		fr->vbr = MPG123_VBR; /* Xing header means always VBR */
	}
	else goto check_lame_tag_no;

	/* we have one of these headers... */
	if(VERBOSE2) fprintf(stderr, "Note: Xing/Lame/Info header detected\n");
	lame_offset += 4; 
	xing_flags = bit_read_long(fr->bsbuf, &lame_offset);
	debug1("Xing: flags 0x%08lx", xing_flags);

	/* From now on, I have to carefully check if the announced data is actually
	   there! I'm always returning 'yes', though.  */
	#define check_bytes_left(n) if(fr->framesize < lame_offset+n) \
		goto check_lame_tag_yes
	if(xing_flags & 1) /* total bitstream frames */
	{
		check_bytes_left(4); long_tmp = bit_read_long(fr->bsbuf, &lame_offset);
		if(fr->p.flags & MPG123_IGNORE_STREAMLENGTH)
		{
			if(VERBOSE3) fprintf(stderr
			,	"Note: Ignoring Xing frames because of MPG123_IGNORE_STREAMLENGTH\n");
		}
		else
		{
			/* Check for endless stream, but: TRACK_MAX_FRAMES sensible at all? */
			fr->track_frames = long_tmp > TRACK_MAX_FRAMES ? 0 : (off_t) long_tmp;
#ifdef GAPLESS
			/* All or nothing: Only if encoder delay/padding is known, we'll cut
			   samples for gapless. */
			if(fr->p.flags & MPG123_GAPLESS)
			frame_gapless_init(fr, fr->track_frames, 0, 0);
#endif
			if(VERBOSE3) fprintf(stderr, "Note: Xing: %lu frames\n", long_tmp);
		}
	}
	if(xing_flags & 0x2) /* total bitstream bytes */
	{
		check_bytes_left(4); long_tmp = bit_read_long(fr->bsbuf, &lame_offset);
		if(fr->p.flags & MPG123_IGNORE_STREAMLENGTH)
		{
			if(VERBOSE3) fprintf(stderr
			,	"Note: Ignoring Xing bytes because of MPG123_IGNORE_STREAMLENGTH\n");
		}
		else
		{
			/* The Xing bitstream length, at least as interpreted by the Lame
			   encoder, encompasses all data from the Xing header frame on,
			   ignoring leading ID3v2 data. Trailing tags (ID3v1) seem to be 
			   included, though. */
			if(fr->rdat.filelen < 1)
			fr->rdat.filelen = (off_t) long_tmp + fr->audio_start; /* Overflow? */
			else
			{
				if((off_t)long_tmp != fr->rdat.filelen - fr->audio_start && NOQUIET)
				{ /* 1/filelen instead of 1/(filelen-start), my decision */
					double diff = 100.0/fr->rdat.filelen
					            * ( fr->rdat.filelen - fr->audio_start
					                - (off_t)long_tmp );
					if(diff < 0.) diff = -diff;

					if(VERBOSE3) fprintf(stderr
					,	"Note: Xing stream size %lu differs by %f%% from determined/given file size!\n"
					,	long_tmp, diff);

					if(diff > 1. && NOQUIET) fprintf(stderr
					,	"Warning: Xing stream size off by more than 1%%, fuzzy seeking may be even more fuzzy than by design!\n");
				}
			}

			if(VERBOSE3) fprintf(stderr, "Note: Xing: %lu bytes\n", long_tmp);
		}
	}
	if(xing_flags & 0x4) /* TOC */
	{
		check_bytes_left(100);
		frame_fill_toc(fr, fr->bsbuf+lame_offset);
		lame_offset += 100;
	}
	if(xing_flags & 0x8) /* VBR quality */
	{
		check_bytes_left(4); long_tmp = bit_read_long(fr->bsbuf, &lame_offset);
		if(VERBOSE3) fprintf(stderr, "Note: Xing: quality = %lu\n", long_tmp);
	}
	/*
		Either zeros/nothing, or:
			0-8: LAME3.90a
			9: revision/VBR method
			10: lowpass
			11-18: ReplayGain
			19: encoder flags
			20: ABR 
			21-23: encoder delays
	*/
	check_bytes_left(24); /* I'm interested in 24 B of extra info. */
	if(fr->bsbuf[lame_offset] != 0)
	{
		unsigned char lame_vbr;
		float replay_gain[2] = {0,0};
		float peak = 0;
		float gain_offset = 0; /* going to be +6 for old lame that used 83dB */
		char nb[10];
		off_t pad_in;
		off_t pad_out;
		memcpy(nb, fr->bsbuf+lame_offset, 9);
		nb[9] = 0;
		if(VERBOSE3) fprintf(stderr, "Note: Info: Encoder: %s\n", nb);
		if(!strncmp("LAME", nb, 4))
		{
			/* Lame versions before 3.95.1 used 83 dB reference level, later
			   versions 89 dB. We stick with 89 dB as being "normal", adding
			   6 dB. */
			unsigned int major, minor;
			char rest[6];
			rest[0] = 0;
			if(sscanf(nb+4, "%u.%u%s", &major, &minor, rest) >= 2)
			{
				debug3("LAME: %u/%u/%s", major, minor, rest);
				/* We cannot detect LAME 3.95 reliably (same version string as
				   3.95.1), so this is a blind spot. Everything < 3.95 is safe,
				   though. */
				if(major < 3 || (major == 3 && minor < 95))
				{
					gain_offset = 6;
					if(VERBOSE3) fprintf(stderr
					,	"Note: Info: Old LAME detected, using ReplayGain preamp of %f dB.\n"
					,	gain_offset);
				}
			}
			else if(VERBOSE3) fprintf(stderr
			,	"Note: Info: Cannot determine LAME version.\n");
		}
		lame_offset += 9; /* 9 in */ 

		/* The 4 big bits are tag revision, the small bits vbr method. */
		lame_vbr = fr->bsbuf[lame_offset] & 15;
		lame_offset += 1; /* 10 in */
		if(VERBOSE3)
		{
			fprintf(stderr, "Note: Info: rev %u\n", fr->bsbuf[lame_offset] >> 4);
			fprintf(stderr, "Note: Info: vbr mode %u\n", lame_vbr);
		}
		switch(lame_vbr)
		{
			/* from rev1 proposal... not sure if all good in practice */
			case 1:
			case 8: fr->vbr = MPG123_CBR; break;
			case 2:
			case 9: fr->vbr = MPG123_ABR; break;
			default: fr->vbr = MPG123_VBR; /* 00==unknown is taken as VBR */
		}
		lame_offset += 1; /* 11 in, skipping lowpass filter value */

		/* ReplayGain peak ampitude, 32 bit float -- why did I parse it as int
		   before??	Ah, yes, Lame seems to store it as int since some day in 2003;
		   I've only seen zeros anyway until now, bah! */
		if
		(
			   (fr->bsbuf[lame_offset]   != 0)
			|| (fr->bsbuf[lame_offset+1] != 0)
			|| (fr->bsbuf[lame_offset+2] != 0)
			|| (fr->bsbuf[lame_offset+3] != 0)
		)
		{
			debug("Wow! Is there _really_ a non-zero peak value? Now is it stored as float or int - how should I know?");
			/* byte*peak_bytes = (byte*) &peak;
			... endianess ... just copy bytes to avoid floating point operation on unaligned memory?
			peak_bytes[0] = ...
			peak = *(float*) (fr->bsbuf+lame_offset); */
		}
		if(VERBOSE3) fprintf(stderr
		,	"Note: Info: peak = %f (I won't use this)\n", peak);
		peak = 0; /* until better times arrived */
		lame_offset += 4; /* 15 in */

		/* ReplayGain values - lame only writes radio mode gain...
		   16bit gain, 3 bits name, 3 bits originator, sign (1=-, 0=+),
		   dB value*10 in 9 bits (fixed point) ignore the setting if name or
		   originator == 000!
		   radio      0 0 1 0 1 1 1 0 0 1 1 1 1 1 0 1
		   audiophile 0 1 0 0 1 0 0 0 0 0 0 1 0 1 0 0 */
		for(i =0; i < 2; ++i)
		{
			unsigned char gt     =  fr->bsbuf[lame_offset] >> 5;
			unsigned char origin = (fr->bsbuf[lame_offset] >> 2) & 0x7;
			float factor         = (fr->bsbuf[lame_offset] & 0x2) ? -0.1f : 0.1f;
			unsigned short gain  = bit_read_short(fr->bsbuf, &lame_offset) & 0x1ff; /* 19 in (2 cycles) */
			if(origin == 0 || gt < 1 || gt > 2) continue;

			--gt;
			replay_gain[gt] = factor * (float) gain;
			/* Apply gain offset for automatic origin. */
			if(origin == 3) replay_gain[gt] += gain_offset;
		}
		if(VERBOSE3) 
		{
			fprintf(stderr, "Note: Info: Radio Gain = %03.1fdB\n"
			,	replay_gain[0]);
			fprintf(stderr, "Note: Info: Audiophile Gain = %03.1fdB\n"
			,	replay_gain[1]);
		}
		for(i=0; i < 2; ++i)
		{
			if(fr->rva.level[i] <= 0)
			{
				fr->rva.peak[i] = 0; /* TODO: use parsed peak? */
				fr->rva.gain[i] = replay_gain[i];
				fr->rva.level[i] = 0;
			}
		}

		lame_offset += 1; /* 20 in, skipping encoding flags byte */

		/* ABR rate */
		if(fr->vbr == MPG123_ABR)
		{
			fr->abr_rate = fr->bsbuf[lame_offset];
			if(VERBOSE3) fprintf(stderr, "Note: Info: ABR rate = %u\n"
			,	fr->abr_rate);
		}
		lame_offset += 1; /* 21 in */
	
		/* Encoder delay and padding, two 12 bit values
		   ... lame does write them from int. */
		pad_in  = ( (((int) fr->bsbuf[lame_offset])   << 4)
		          | (((int) fr->bsbuf[lame_offset+1]) >> 4) );
		pad_out = ( (((int) fr->bsbuf[lame_offset+1]) << 8)
		          |  ((int) fr->bsbuf[lame_offset+2])       ) & 0xfff;
		lame_offset += 3; /* 24 in */
		if(VERBOSE3) fprintf(stderr, "Note: Encoder delay = %i; padding = %i\n"
		,	(int)pad_in, (int)pad_out);
		#ifdef GAPLESS
		if(fr->p.flags & MPG123_GAPLESS)
		frame_gapless_init(fr, fr->track_frames, pad_in, pad_out);
		#endif
		/* final: 24 B LAME data */
	}

check_lame_tag_yes:
	/* switch buffer back ... */
	fr->bsbuf = fr->bsspace[fr->bsnum]+512;
	fr->bsnum = (fr->bsnum + 1) & 1;
	return 1;
check_lame_tag_no:
	return 0;
}