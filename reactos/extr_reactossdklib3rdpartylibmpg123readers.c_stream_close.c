#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/ * iohandle; int /*<<< orphan*/  (* cleanup_handle ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  buffer; scalar_t__ filept; } ;
struct TYPE_5__ {TYPE_1__ rdat; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int READER_BUFFERED ; 
 int READER_FD_OPENED ; 
 int READER_HANDLEIO ; 
 int /*<<< orphan*/  bc_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_close (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stream_close(mpg123_handle *fr)
{
	if(fr->rdat.flags & READER_FD_OPENED) compat_close(fr->rdat.filept);

	fr->rdat.filept = 0;

#ifndef NO_FEEDER
	if(fr->rdat.flags & READER_BUFFERED)  bc_reset(&fr->rdat.buffer);
#endif
	if(fr->rdat.flags & READER_HANDLEIO)
	{
		if(fr->rdat.cleanup_handle != NULL) fr->rdat.cleanup_handle(fr->rdat.iohandle);

		fr->rdat.iohandle = NULL;
	}
}