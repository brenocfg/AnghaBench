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
 int /*<<< orphan*/  _mbset (unsigned char*,int) ; 
 void* _mbsinc (unsigned char*) ; 
 int _mbsnextc (unsigned char const*) ; 

unsigned char *_mbsncat (unsigned char *dst, const unsigned char *src, size_t n)
{
    int c;
    unsigned char *save = dst;

    while ((c = _mbsnextc (dst)))
	dst = _mbsinc (dst);

    while (n-- > 0 && (c = _mbsnextc (src))) {

	_mbset (dst, c);

	dst = _mbsinc (dst);

	src = _mbsinc ((unsigned char *) src);

    }

    *dst = '\0';

    return save;
}