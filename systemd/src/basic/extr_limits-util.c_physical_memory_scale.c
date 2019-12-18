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
typedef  int uint64_t ;

/* Variables and functions */
 int UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int page_size () ; 
 int physical_memory () ; 

uint64_t physical_memory_scale(uint64_t v, uint64_t max) {
        uint64_t p, m, ps, r;

        assert(max > 0);

        /* Returns the physical memory size, multiplied by v divided by max. Returns UINT64_MAX on overflow. On success
         * the result is a multiple of the page size (rounds down). */

        ps = page_size();
        assert(ps > 0);

        p = physical_memory() / ps;
        assert(p > 0);

        m = p * v;
        if (m / p != v)
                return UINT64_MAX;

        m /= max;

        r = m * ps;
        if (r / ps != m)
                return UINT64_MAX;

        return r;
}