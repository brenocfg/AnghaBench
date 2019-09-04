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
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ (* fdread ) (TYPE_2__*,unsigned char*,scalar_t__) ;int flags; int /*<<< orphan*/  filepos; } ;
struct TYPE_6__ {TYPE_1__ rdat; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int READER_BUFFERED ; 
 scalar_t__ READER_ERROR ; 
 scalar_t__ stub1 (TYPE_2__*,unsigned char*,scalar_t__) ; 

__attribute__((used)) static ssize_t plain_fullread(mpg123_handle *fr,unsigned char *buf, ssize_t count)
{
	ssize_t ret,cnt=0;

#ifdef EXTRA_DEBUG
	debug1("plain fullread of %"SSIZE_P, (size_p)count);
#endif
	/*
		There used to be a check for expected file end here (length value or ID3 flag).
		This is not needed:
		1. EOF is indicated by fdread returning zero bytes anyway.
		2. We get false positives of EOF for either files that grew or
		3. ... files that have ID3v1 tags in between (stream with intro).
	*/
	while(cnt < count)
	{
		ret = fr->rdat.fdread(fr,buf+cnt,count-cnt);
		if(ret < 0) return READER_ERROR;
		if(ret == 0) break;
		if(!(fr->rdat.flags & READER_BUFFERED)) fr->rdat.filepos += ret;
		cnt += ret;
	}
	return cnt;
}