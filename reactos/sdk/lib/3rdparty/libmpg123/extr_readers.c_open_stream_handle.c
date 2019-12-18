#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int filelen; int filept; int /*<<< orphan*/  flags; void* iohandle; } ;
struct TYPE_6__ {TYPE_1__ rdat; int /*<<< orphan*/  icy; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  READER_HANDLEIO ; 
 int /*<<< orphan*/  clear_icy (int /*<<< orphan*/ *) ; 
 int open_finish (TYPE_2__*) ; 

int open_stream_handle(mpg123_handle *fr, void *iohandle)
{
	clear_icy(&fr->icy); /* can be done inside frame_clear ...? */
	fr->rdat.filelen = -1;
	fr->rdat.filept  = -1;
	fr->rdat.iohandle = iohandle;
	fr->rdat.flags = 0;
	fr->rdat.flags |= READER_HANDLEIO;

	return open_finish(fr);
}