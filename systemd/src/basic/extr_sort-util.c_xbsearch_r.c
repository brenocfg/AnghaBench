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
typedef  int (* __compar_d_fn_t ) (void const*,void const*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  size_multiply_overflow (size_t,size_t) ; 

void *xbsearch_r(const void *key, const void *base, size_t nmemb, size_t size,
                 __compar_d_fn_t compar, void *arg) {
        size_t l, u, idx;
        const void *p;
        int comparison;

        assert(!size_multiply_overflow(nmemb, size));

        l = 0;
        u = nmemb;
        while (l < u) {
                idx = (l + u) / 2;
                p = (const uint8_t*) base + idx * size;
                comparison = compar(key, p, arg);
                if (comparison < 0)
                        u = idx;
                else if (comparison > 0)
                        l = idx + 1;
                else
                        return (void *)p;
        }
        return NULL;
}