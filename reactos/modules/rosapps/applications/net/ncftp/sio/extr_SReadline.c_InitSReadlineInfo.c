#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int malloc; char* buf; size_t bufSize; size_t bufSizeMax; char* bufLim; int fd; int timeoutLen; int requireEOLN; char* bufPtr; } ;
typedef  TYPE_1__ SReadlineInfo ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

int
InitSReadlineInfo(SReadlineInfo *srl, int fd, char *buf, size_t bsize, int tlen, int requireEOLN)
{
	if (buf == NULL) {
		if (bsize < 512)
			bsize = 512;	/* Pointless, otherwise. */
		buf = (char *) malloc(bsize);
		if (buf == NULL)
			return (-1);
		srl->malloc = 1;
	} else {
		srl->malloc = 0;
	}
	memset(buf, 0, bsize);
	srl->buf = buf;
	srl->bufSize = bsize;
	srl->bufSizeMax = bsize;
	srl->bufLim = srl->buf + bsize;
	srl->fd = fd;
	srl->timeoutLen = tlen;
	srl->requireEOLN = requireEOLN;

	/* This line sets the buffer pointer
	 * so that the first thing to do is reset and fill the buffer
	 * using real I/O.
	 */
	srl->bufPtr = srl->bufLim;
	return (0);
}