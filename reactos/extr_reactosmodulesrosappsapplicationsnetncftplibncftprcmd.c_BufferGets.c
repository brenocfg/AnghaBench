#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ read (int,char*,size_t) ; 

int
BufferGets(char *buf, size_t bufsize, int inStream, char *secondaryBuf, char **secBufPtr, char **secBufLimit, size_t secBufSize)
{
	int err;
	char *src;
	char *dst;
	char *dstlim;
	int len;
	int nr;
	int haveEof = 0;

	err = 0;
	dst = buf;
	dstlim = dst + bufsize - 1;		/* Leave room for NUL. */
	src = (*secBufPtr);
	for ( ; dst < dstlim; ) {
		if (src >= (*secBufLimit)) {
			/* Fill the buffer. */

/* Don't need to poll it here.  The routines that use BufferGets don't
 * need any special processing during timeouts (i.e. progress reports),
 * so go ahead and just let it block until there is data to read.
 */
			nr = (int) read(inStream, secondaryBuf, secBufSize);
			if (nr == 0) {
				/* EOF. */
				haveEof = 1;
				goto done;
			} else if (nr < 0) {
				/* Error. */
				err = -1;
				goto done;
			}
			(*secBufPtr) = secondaryBuf;
			(*secBufLimit) = secondaryBuf + nr;
			src = (*secBufPtr);
			if (nr < (int) secBufSize)
				src[nr] = '\0';
		}
		if (*src == '\r') {
			++src;
		} else {
			if (*src == '\n') {
				/* *dst++ = *src++; */	++src;
				goto done;
			}
			*dst++ = *src++;
		}
	}

done:
	(*secBufPtr) = src;
	*dst = '\0';
	len = (int) (dst - buf);
	if (err < 0)
		return (err);
	if ((len == 0) && (haveEof == 1))
		return (-1);
	return (len);	/* May be zero, if a blank line. */
}