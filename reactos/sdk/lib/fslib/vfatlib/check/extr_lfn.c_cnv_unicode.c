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
 int /*<<< orphan*/  BYTES_TO_WCHAR (unsigned char const,unsigned char const) ; 
 scalar_t__ UNICODE_CONVERTABLE (unsigned char const,unsigned char const) ; 
 unsigned char* alloc (int) ; 
 unsigned char* fat_uni2esc ; 
 size_t mbslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_queue ; 
 unsigned char* qalloc (int /*<<< orphan*/ *,int) ; 
 size_t wctombs (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *cnv_unicode(const unsigned char *uni, int maxlen, int use_q)
{
    const unsigned char *up;
    unsigned char *out, *cp;
    int len, val;
    size_t x;

    for (len = 0, up = uni; (up - uni) / 2 < maxlen && (up[0] || up[1]);
	 up += 2) {
	if ((x = mbslen(BYTES_TO_WCHAR(up[0], up[1]))) != (size_t) - 1)
	    len += x;
	else if (UNICODE_CONVERTABLE(up[0], up[1]))
	    ++len;
	else
	    len += 4;
    }
    cp = out = use_q ? qalloc(&mem_queue, len + 1) : alloc(len + 1);

    for (up = uni; (up - uni) / 2 < maxlen && (up[0] || up[1]); up += 2) {
	if ((x =
	     wctombs((char *)cp, BYTES_TO_WCHAR(up[0], up[1]))) != (size_t) - 1)
	    cp += x;
	else if (UNICODE_CONVERTABLE(up[0], up[1]))
	    *cp++ = up[0];
	else {
	    /* here the same escape notation is used as in the Linux kernel */
	    *cp++ = ':';
	    val = (up[1] << 8) + up[0];
	    cp[2] = fat_uni2esc[val & 0x3f];
	    val >>= 6;
	    cp[1] = fat_uni2esc[val & 0x3f];
	    val >>= 6;
	    cp[0] = fat_uni2esc[val & 0x3f];
	    cp += 3;
	}
    }
    *cp = 0;

    return (char *)out;
}