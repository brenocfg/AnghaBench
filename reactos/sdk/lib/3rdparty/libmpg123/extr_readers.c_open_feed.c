#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ flags; } ;
struct TYPE_8__ {scalar_t__ icy_interval; } ;
struct TYPE_9__ {TYPE_5__* rd; TYPE_1__ rdat; int /*<<< orphan*/  icy; TYPE_2__ p; int /*<<< orphan*/  err; } ;
typedef  TYPE_3__ mpg123_handle ;
struct TYPE_10__ {scalar_t__ (* init ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPG123_MISSING_FEATURE ; 
 scalar_t__ NOQUIET ; 
 size_t READER_FEED ; 
 int /*<<< orphan*/  clear_icy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_5__* readers ; 
 scalar_t__ stub1 (TYPE_3__*) ; 

int open_feed(mpg123_handle *fr)
{
	debug("feed reader");
#ifdef NO_FEEDER
	error("Buffered readers not supported in this build.");
	fr->err = MPG123_MISSING_FEATURE;
	return -1;
#else
#ifndef NO_ICY
	if(fr->p.icy_interval > 0)
	{
		if(NOQUIET) error("Feed reader cannot do ICY parsing!");

		return -1;
	}
	clear_icy(&fr->icy);
#endif
	fr->rd = &readers[READER_FEED];
	fr->rdat.flags = 0;
	if(fr->rd->init(fr) < 0) return -1;

	debug("feed reader init successful");
	return 0;
#endif /* NO_FEEDER */
}