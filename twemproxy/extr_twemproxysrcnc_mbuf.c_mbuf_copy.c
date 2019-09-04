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
typedef  int /*<<< orphan*/  uint8_t ;
struct mbuf {size_t last; int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  mbuf_full (struct mbuf*) ; 
 size_t mbuf_size (struct mbuf*) ; 
 int /*<<< orphan*/  nc_memcpy (size_t,int /*<<< orphan*/ *,size_t) ; 

void
mbuf_copy(struct mbuf *mbuf, uint8_t *pos, size_t n)
{
    if (n == 0) {
        return;
    }

    /* mbuf has space for n bytes */
    ASSERT(!mbuf_full(mbuf) && n <= mbuf_size(mbuf));

    /* no overlapping copy */
    ASSERT(pos < mbuf->start || pos >= mbuf->end);

    nc_memcpy(mbuf->last, pos, n);
    mbuf->last += n;
}