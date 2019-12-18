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
struct TYPE_5__ {int filelen; int filept; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ rdat; int /*<<< orphan*/  err; int /*<<< orphan*/  icy; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MPG123_BAD_FILE ; 
 int MPG123_ERR ; 
 scalar_t__ NOQUIET ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  READER_FD_OPENED ; 
 int /*<<< orphan*/  clear_icy (int /*<<< orphan*/ *) ; 
 int compat_open (char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error2 (char*,char const*,int /*<<< orphan*/ ) ; 
 int open_finish (TYPE_2__*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int open_stream(mpg123_handle *fr, const char *bs_filenam, int fd)
{
	int filept_opened = 1;
	int filept; /* descriptor of opened file/stream */

	clear_icy(&fr->icy); /* can be done inside frame_clear ...? */

	if(!bs_filenam) /* no file to open, got a descriptor (stdin) */
	{
		filept = fd;
		filept_opened = 0; /* and don't try to close it... */
	}
	#ifndef O_BINARY
	#define O_BINARY (0)
	#endif
	else if((filept = compat_open(bs_filenam, O_RDONLY|O_BINARY)) < 0) /* a plain old file to open... */
	{
		if(NOQUIET) error2("Cannot open file %s: %s", bs_filenam, strerror(errno));
		fr->err = MPG123_BAD_FILE;
		return MPG123_ERR; /* error... */
	}

	/* now we have something behind filept and can init the reader */
	fr->rdat.filelen = -1;
	fr->rdat.filept  = filept;
	fr->rdat.flags = 0;
	if(filept_opened)	fr->rdat.flags |= READER_FD_OPENED;

	return open_finish(fr);
}