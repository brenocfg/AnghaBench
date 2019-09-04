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
typedef  scalar_t__ wchar_t ;
struct utf8_table {int cmask; int cval; long lmask; long lval; } ;
typedef  int __u8 ;

/* Variables and functions */
 struct utf8_table* utf8_table ; 

int
utf8_mbtowc(wchar_t *p, const __u8 *s, int n)
{
    long l;
    int c0, c, nc;
    struct utf8_table *t;

    nc = 0;
    c0 = *s;
    l = c0;
    for (t = utf8_table; t->cmask; t++) {
        nc++;
        if ((c0 & t->cmask) == t->cval) {
            l &= t->lmask;
            if (l < t->lval)
                return -1;
            *p = (wchar_t)l;
            return nc;
        }
        if (n <= nc)
            return -1;
        s++;
        c = (*s ^ 0x80) & 0xFF;
        if (c & 0xC0)
            return -1;
        l = (l << 6) | c;
    }
    return -1;
}