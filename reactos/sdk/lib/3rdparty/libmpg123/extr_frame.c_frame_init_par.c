#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mpg123_pars_struct {int dummy; } ;
typedef  int /*<<< orphan*/  mpg123_pars ;
struct TYPE_16__ {int /*<<< orphan*/  feedbuffer; int /*<<< orphan*/  feedpool; } ;
struct TYPE_14__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/ * cleanup_handle; int /*<<< orphan*/ * r_lseek_handle; int /*<<< orphan*/ * r_read_handle; int /*<<< orphan*/ * iohandle; int /*<<< orphan*/ * r_lseek; int /*<<< orphan*/ * r_read; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; int /*<<< orphan*/  class; } ;
struct TYPE_12__ {scalar_t__ size; scalar_t__ fill; int /*<<< orphan*/ * rdata; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int* ntom_val; int ntom_step; int decoder_change; int /*<<< orphan*/  index; int /*<<< orphan*/ * make_decode_tables; int /*<<< orphan*/ * synth_mono; int /*<<< orphan*/ * synth; scalar_t__ down_sample; TYPE_6__ p; TYPE_3__ rdat; int /*<<< orphan*/  err; int /*<<< orphan*/ * wrapperclean; int /*<<< orphan*/ * wrapperdata; int /*<<< orphan*/  af; int /*<<< orphan*/  icy; TYPE_2__ cpu_opts; int /*<<< orphan*/ * xing_toc; int /*<<< orphan*/ * layerscratch; int /*<<< orphan*/ * dithernoise; int /*<<< orphan*/ * conv16to8_buf; scalar_t__ rawdecwins; int /*<<< orphan*/ * rawdecwin; scalar_t__ rawbuffss; int /*<<< orphan*/ * rawbuffs; TYPE_1__ buffer; int /*<<< orphan*/  own_buffer; } ;
typedef  TYPE_4__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MPG123_OK ; 
 int NTOM_MUL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bc_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defdec () ; 
 int /*<<< orphan*/  fi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_default_pars (TYPE_6__*) ; 
 int /*<<< orphan*/  frame_fixed_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  frame_index_setup (TYPE_4__*) ; 
 int /*<<< orphan*/  init_icy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_id3 (TYPE_4__*) ; 
 int /*<<< orphan*/  invalidate_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpg123_reset_eq (TYPE_4__*) ; 

void frame_init_par(mpg123_handle *fr, mpg123_pars *mp)
{
	fr->own_buffer = TRUE;
	fr->buffer.data = NULL;
	fr->buffer.rdata = NULL;
	fr->buffer.fill = 0;
	fr->buffer.size = 0;
	fr->rawbuffs = NULL;
	fr->rawbuffss = 0;
	fr->rawdecwin = NULL;
	fr->rawdecwins = 0;
#ifndef NO_8BIT
	fr->conv16to8_buf = NULL;
#endif
#ifdef OPT_DITHER
	fr->dithernoise = NULL;
#endif
	fr->layerscratch = NULL;
	fr->xing_toc = NULL;
	fr->cpu_opts.type = defdec();
	fr->cpu_opts.class = decclass(fr->cpu_opts.type);
#ifndef NO_NTOM
	/* these two look unnecessary, check guarantee for synth_ntom_set_step (in control_generic, even)! */
	fr->ntom_val[0] = NTOM_MUL>>1;
	fr->ntom_val[1] = NTOM_MUL>>1;
	fr->ntom_step = NTOM_MUL;
#endif
	/* unnecessary: fr->buffer.size = fr->buffer.fill = 0; */
	mpg123_reset_eq(fr);
	init_icy(&fr->icy);
	init_id3(fr);
	/* frame_outbuffer is missing... */
	/* frame_buffers is missing... that one needs cpu opt setting! */
	/* after these... frame_reset is needed before starting full decode */
	invalidate_format(&fr->af);
	fr->rdat.r_read = NULL;
	fr->rdat.r_lseek = NULL;
	fr->rdat.iohandle = NULL;
	fr->rdat.r_read_handle = NULL;
	fr->rdat.r_lseek_handle = NULL;
	fr->rdat.cleanup_handle = NULL;
	fr->wrapperdata = NULL;
	fr->wrapperclean = NULL;
	fr->decoder_change = 1;
	fr->err = MPG123_OK;
	if(mp == NULL) frame_default_pars(&fr->p);
	else memcpy(&fr->p, mp, sizeof(struct mpg123_pars_struct));

#ifndef NO_FEEDER
	bc_prepare(&fr->rdat.buffer, fr->p.feedpool, fr->p.feedbuffer);
#endif

	fr->down_sample = 0; /* Initialize to silence harmless errors when debugging. */
	frame_fixed_reset(fr); /* Reset only the fixed data, dynamic buffers are not there yet! */
	fr->synth = NULL;
	fr->synth_mono = NULL;
	fr->make_decode_tables = NULL;
#ifdef FRAME_INDEX
	fi_init(&fr->index);
	frame_index_setup(fr); /* Apply the size setting. */
#endif
}