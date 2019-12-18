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
struct bufferchain {scalar_t__ size; scalar_t__ pos; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  readbuf ;
struct TYPE_5__ {scalar_t__ (* fullread ) (TYPE_2__*,unsigned char*,int) ;struct bufferchain buffer; } ;
struct TYPE_6__ {TYPE_1__ rdat; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 scalar_t__ NOQUIET ; 
 scalar_t__ READER_ERROR ; 
 scalar_t__ VERBOSE3 ; 
 int bc_add (struct bufferchain*,unsigned char*,scalar_t__) ; 
 scalar_t__ bc_give (struct bufferchain*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  debug1 (char*,long) ; 
 int /*<<< orphan*/  debug2 (char*,long,long) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error1 (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (TYPE_2__*,unsigned char*,int) ; 

__attribute__((used)) static ssize_t buffered_fullread(mpg123_handle *fr, unsigned char *out, ssize_t count)
{
	struct bufferchain *bc = &fr->rdat.buffer;
	ssize_t gotcount;
	if(bc->size - bc->pos < count)
	{ /* Add more stuff to buffer. If hitting end of file, adjust count. */
		unsigned char readbuf[4096];
		ssize_t need = count - (bc->size-bc->pos);
		while(need>0)
		{
			int ret;
			ssize_t got = fr->rdat.fullread(fr, readbuf, sizeof(readbuf));
			if(got < 0)
			{
				if(NOQUIET) error("buffer reading");
				return READER_ERROR;
			}

			if(VERBOSE3) debug1("buffered_fullread: buffering %li bytes from stream (if > 0)", (long)got);
			if(got > 0 && (ret=bc_add(bc, readbuf, got)) != 0)
			{
				if(NOQUIET) error1("unable to add to chain, return: %i", ret);
				return READER_ERROR;
			}

			need -= got; /* May underflow here... */
			if(got < sizeof(readbuf)) /* That naturally catches got == 0, too. */
			{
				if(VERBOSE3) fprintf(stderr, "Note: Input data end.\n");
				break; /* End. */
			}
		}
		if(bc->size - bc->pos < count)
		count = bc->size - bc->pos; /* We want only what we got. */
	}
	gotcount = bc_give(bc, out, count);

	if(VERBOSE3) debug2("wanted %li, got %li", (long)count, (long)gotcount);

	if(gotcount != count){ if(NOQUIET) error("gotcount != count"); return READER_ERROR; }
	else return gotcount;
}