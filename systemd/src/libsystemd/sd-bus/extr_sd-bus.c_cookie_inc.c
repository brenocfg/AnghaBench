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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ COOKIE_CYCLED ; 
 scalar_t__ UINT32_MAX ; 

__attribute__((used)) static uint64_t cookie_inc(uint64_t cookie) {

        /* Stay within the 32bit range, since classic D-Bus can't deal with more */
        if (cookie >= UINT32_MAX)
                return COOKIE_CYCLED; /* Don't go back to zero, but use the highest bit for checking
                                       * whether we are looping. */

        return cookie + 1;
}