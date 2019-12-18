#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fileoff; scalar_t__ firstpos; scalar_t__ pos; } ;
struct TYPE_7__ {int flags; TYPE_1__ buffer; int /*<<< orphan*/  filepos; } ;
struct TYPE_8__ {TYPE_2__ rdat; } ;
typedef  TYPE_3__ mpg123_handle ;

/* Variables and functions */
 int READER_BUFFERED ; 
 int READER_SEEKABLE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  stream_lseek (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stream_rewind(mpg123_handle *fr)
{
	if(fr->rdat.flags & READER_SEEKABLE)
	{
		fr->rdat.filepos = stream_lseek(fr,0,SEEK_SET);
#ifndef NO_FEEDER
		fr->rdat.buffer.fileoff = fr->rdat.filepos;
#endif
	}
#ifndef NO_FEEDER
	if(fr->rdat.flags & READER_BUFFERED)
	{
		fr->rdat.buffer.pos      = 0;
		fr->rdat.buffer.firstpos = 0;
		fr->rdat.filepos = fr->rdat.buffer.fileoff;
	}
#endif
}