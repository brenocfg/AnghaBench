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
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ USEC_INFINITY ; 
 scalar_t__ map_clock_id (int /*<<< orphan*/ ) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 scalar_t__ usec_add (scalar_t__,scalar_t__) ; 
 scalar_t__ usec_sub_unsigned (scalar_t__,scalar_t__) ; 

usec_t usec_shift_clock(usec_t x, clockid_t from, clockid_t to) {
        usec_t a, b;

        if (x == USEC_INFINITY)
                return USEC_INFINITY;
        if (map_clock_id(from) == map_clock_id(to))
                return x;

        a = now(from);
        b = now(to);

        if (x > a)
                /* x lies in the future */
                return usec_add(b, usec_sub_unsigned(x, a));
        else
                /* x lies in the past */
                return usec_sub_unsigned(b, usec_sub_unsigned(a, x));
}