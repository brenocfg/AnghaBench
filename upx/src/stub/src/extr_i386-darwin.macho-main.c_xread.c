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
struct TYPE_3__ {unsigned char* buf; size_t size; } ;
typedef  TYPE_1__ Extent ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STR_xread () ; 
 int /*<<< orphan*/  STR_xreadfail () ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void
xread(Extent *x, void *buf, size_t count)
{
    unsigned char *p=x->buf, *q=buf;
    size_t j;
    DPRINTF((STR_xread(), x, x->size, x->buf, buf, count));
    if (x->size < count) {
        DPRINTF((STR_xreadfail(), x, x->size, x->buf, buf, count));
        exit(127);
    }
    for (j = count; 0!=j--; ++p, ++q) {
        *q = *p;
    }
    x->buf  += count;
    x->size -= count;
}