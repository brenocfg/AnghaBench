#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_10__ {scalar_t__ pos; } ;
struct TYPE_11__ {int flags; TYPE_1__ buffer; } ;
struct TYPE_13__ {void* err; TYPE_3__* rd; TYPE_2__ rdat; } ;
typedef  TYPE_4__ mpg123_handle ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_12__ {scalar_t__ (* fullread ) (TYPE_4__*,unsigned char*,scalar_t__) ;scalar_t__ (* tell ) (TYPE_4__*) ;} ;

/* Variables and functions */
 void* MPG123_NO_SEEK ; 
 int READER_BUFFERED ; 
 scalar_t__ READER_ERROR ; 
 int READER_SEEKABLE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ stream_lseek (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_4__*,unsigned char*,scalar_t__) ; 
 scalar_t__ stub2 (TYPE_4__*) ; 
 scalar_t__ stub3 (TYPE_4__*) ; 

__attribute__((used)) static off_t stream_skip_bytes(mpg123_handle *fr,off_t len)
{
	if(fr->rdat.flags & READER_SEEKABLE)
	{
		off_t ret = stream_lseek(fr, len, SEEK_CUR);
		return (ret < 0) ? READER_ERROR : ret;
	}
	else if(len >= 0)
	{
		unsigned char buf[1024]; /* ThOr: Compaq cxx complained and it makes sense to me... or should one do a cast? What for? */
		ssize_t ret;
		while (len > 0)
		{
			ssize_t num = len < (off_t)sizeof(buf) ? (ssize_t)len : (ssize_t)sizeof(buf);
			ret = fr->rd->fullread(fr, buf, num);
			if (ret < 0) return ret;
			else if(ret == 0) break; /* EOF... an error? interface defined to tell the actual position... */
			len -= ret;
		}
		return fr->rd->tell(fr);
	}
#ifndef NO_FEEDER
	else if(fr->rdat.flags & READER_BUFFERED)
	{ /* Perhaps we _can_ go a bit back. */
		if(fr->rdat.buffer.pos >= -len)
		{
			fr->rdat.buffer.pos += len;
			return fr->rd->tell(fr);
		}
		else
		{
			fr->err = MPG123_NO_SEEK;
			return READER_ERROR;
		}
	}
#endif
	else
	{
		fr->err = MPG123_NO_SEEK;
		return READER_ERROR;
	}
}