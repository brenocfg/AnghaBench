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
struct TYPE_7__ {scalar_t__ interval; scalar_t__ next; } ;
struct TYPE_8__ {scalar_t__ icy_interval; } ;
struct TYPE_9__ {TYPE_5__* rd; TYPE_1__ icy; TYPE_2__ p; } ;
typedef  TYPE_3__ mpg123_handle ;
struct TYPE_10__ {scalar_t__ (* init ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int MPG123_OK ; 
 size_t READER_ICY_STREAM ; 
 size_t READER_STREAM ; 
 int /*<<< orphan*/  debug (char*) ; 
 TYPE_5__* readers ; 
 scalar_t__ stub1 (TYPE_3__*) ; 

__attribute__((used)) static int open_finish(mpg123_handle *fr)
{
#ifndef NO_ICY
	if(fr->p.icy_interval > 0)
	{
		debug("ICY reader");
		fr->icy.interval = fr->p.icy_interval;
		fr->icy.next = fr->icy.interval;
		fr->rd = &readers[READER_ICY_STREAM];
	}
	else
#endif
	{
		fr->rd = &readers[READER_STREAM];
		debug("stream reader");
	}

	if(fr->rd->init(fr) < 0) return -1;

	return MPG123_OK;
}