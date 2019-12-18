#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_5__ {scalar_t__ pos; scalar_t__ fileoff; } ;
struct TYPE_6__ {int flags; scalar_t__ filepos; TYPE_1__ buffer; } ;
struct TYPE_7__ {TYPE_2__ rdat; } ;
typedef  TYPE_3__ mpg123_handle ;

/* Variables and functions */
 int READER_BUFFERED ; 

__attribute__((used)) static off_t generic_tell(mpg123_handle *fr)
{
#ifndef NO_FEEDER
	if(fr->rdat.flags & READER_BUFFERED)
	fr->rdat.filepos = fr->rdat.buffer.fileoff+fr->rdat.buffer.pos;
#endif

	return fr->rdat.filepos;
}