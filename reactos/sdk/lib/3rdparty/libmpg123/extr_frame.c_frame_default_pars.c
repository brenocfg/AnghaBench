#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double outscale; int resync_limit; int preframes; int feedpool; int feedbuffer; int /*<<< orphan*/  index_size; scalar_t__ timeout; scalar_t__ icy_interval; scalar_t__ verbose; scalar_t__ doublespeed; scalar_t__ halfspeed; scalar_t__ rva; scalar_t__ down_sample; scalar_t__ force_rate; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ mpg123_pars ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_SIZE ; 
 int /*<<< orphan*/  MPG123_AUTO_RESAMPLE ; 
 int /*<<< orphan*/  MPG123_GAPLESS ; 
 int /*<<< orphan*/  mpg123_fmt_all (TYPE_1__*) ; 

__attribute__((used)) static void frame_default_pars(mpg123_pars *mp)
{
	mp->outscale = 1.0;
	mp->flags = 0;
#ifdef GAPLESS
	mp->flags |= MPG123_GAPLESS;
#endif
	mp->flags |= MPG123_AUTO_RESAMPLE;
#ifndef NO_NTOM
	mp->force_rate = 0;
#endif
	mp->down_sample = 0;
	mp->rva = 0;
	mp->halfspeed = 0;
	mp->doublespeed = 0;
	mp->verbose = 0;
#ifndef NO_ICY
	mp->icy_interval = 0;
#endif
	mp->timeout = 0;
	mp->resync_limit = 1024;
#ifdef FRAME_INDEX
	mp->index_size = INDEX_SIZE;
#endif
	mp->preframes = 4; /* That's good  for layer 3 ISO compliance bitstream. */
	mpg123_fmt_all(mp);
	/* Default of keeping some 4K buffers at hand, should cover the "usual" use case (using 16K pipe buffers as role model). */
#ifndef NO_FEEDER
	mp->feedpool = 5; 
	mp->feedbuffer = 4096;
#endif
}