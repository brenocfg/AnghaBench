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
struct TYPE_7__ {scalar_t__ timeout_sec; int filelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  buffer; int /*<<< orphan*/  fullread; scalar_t__ filepos; int /*<<< orphan*/ * lseek; int /*<<< orphan*/ * r_lseek; int /*<<< orphan*/ * r_read; int /*<<< orphan*/ * read; int /*<<< orphan*/  fdread; int /*<<< orphan*/  filept; } ;
struct TYPE_6__ {scalar_t__ timeout; scalar_t__ icy_interval; int flags; } ;
struct TYPE_8__ {TYPE_2__ rdat; int /*<<< orphan*/ * rd; int /*<<< orphan*/  err; TYPE_1__ p; int /*<<< orphan*/  metaflags; scalar_t__ id3buf; } ;
typedef  TYPE_3__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int MPG123_FORCE_SEEKABLE ; 
 int /*<<< orphan*/  MPG123_MISSING_FEATURE ; 
 int /*<<< orphan*/  MPG123_NEW_ID3 ; 
 int MPG123_NO_PEEK_END ; 
 int MPG123_SEEKBUFFER ; 
 scalar_t__ NOQUIET ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  READER_BUFFERED ; 
 size_t READER_BUF_ICY_STREAM ; 
 size_t READER_BUF_STREAM ; 
 size_t READER_ICY_STREAM ; 
 int /*<<< orphan*/  READER_ID3TAG ; 
 int /*<<< orphan*/  READER_NONBLOCK ; 
 int /*<<< orphan*/  READER_SEEKABLE ; 
 size_t READER_STREAM ; 
 int /*<<< orphan*/  bc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int get_fileinfo (TYPE_3__*) ; 
 int /*<<< orphan*/  icy_fullread ; 
 int /*<<< orphan*/ * nix_lseek ; 
 int /*<<< orphan*/  plain_fullread ; 
 int /*<<< orphan*/  plain_read ; 
 int /*<<< orphan*/ * posix_lseek ; 
 int /*<<< orphan*/ * posix_read ; 
 int /*<<< orphan*/ * readers ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  timeout_read ; 

__attribute__((used)) static int default_init(mpg123_handle *fr)
{
#ifdef TIMEOUT_READ
	if(fr->p.timeout > 0)
	{
		int flags;
		if(fr->rdat.r_read != NULL)
		{
			error("Timeout reading does not work with user-provided read function. Implement it yourself!");
			return -1;
		}
		flags = fcntl(fr->rdat.filept, F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(fr->rdat.filept, F_SETFL, flags);
		fr->rdat.fdread = timeout_read;
		fr->rdat.timeout_sec = fr->p.timeout;
		fr->rdat.flags |= READER_NONBLOCK;
	}
	else
#endif
	fr->rdat.fdread = plain_read;

	fr->rdat.read  = fr->rdat.r_read  != NULL ? fr->rdat.r_read  : posix_read;
	fr->rdat.lseek = fr->rdat.r_lseek != NULL ? fr->rdat.r_lseek : posix_lseek;
#ifndef NO_ICY
	/* ICY streams of any sort shall not be seekable. */
	if(fr->p.icy_interval > 0) fr->rdat.lseek = nix_lseek;
#endif

	fr->rdat.filelen = fr->p.flags & MPG123_NO_PEEK_END ? -1 : get_fileinfo(fr);
	fr->rdat.filepos = 0;
	if(fr->p.flags & MPG123_FORCE_SEEKABLE)
		fr->rdat.flags |= READER_SEEKABLE;
	/*
		Don't enable seeking on ICY streams, just plain normal files.
		This check is necessary since the client can enforce ICY parsing on files that would otherwise be seekable.
		It is a task for the future to make the ICY parsing safe with seeks ... or not.
	*/
	if(fr->rdat.filelen >= 0)
	{
		fr->rdat.flags |= READER_SEEKABLE;
		if(!strncmp((char*)fr->id3buf,"TAG",3))
		{
			fr->rdat.flags |= READER_ID3TAG;
			fr->metaflags  |= MPG123_NEW_ID3;
		}
	}
	/* Switch reader to a buffered one, if allowed. */
	else if(fr->p.flags & MPG123_SEEKBUFFER)
	{
#ifdef NO_FEEDER
		error("Buffered readers not supported in this build.");
		fr->err = MPG123_MISSING_FEATURE;
		return -1;
#else
		if     (fr->rd == &readers[READER_STREAM])
		{
			fr->rd = &readers[READER_BUF_STREAM];
			fr->rdat.fullread = plain_fullread;
		}
#ifndef NO_ICY
		else if(fr->rd == &readers[READER_ICY_STREAM])
		{
			fr->rd = &readers[READER_BUF_ICY_STREAM];
			fr->rdat.fullread = icy_fullread;
		}
#endif
		else
		{
			if(NOQUIET) error("mpg123 Programmer's fault: invalid reader");
			return -1;
		}
		bc_init(&fr->rdat.buffer);
		fr->rdat.filelen = 0; /* We carry the offset, but never know how big the stream is. */
		fr->rdat.flags |= READER_BUFFERED;
#endif /* NO_FEEDER */
	}
	return 0;
}