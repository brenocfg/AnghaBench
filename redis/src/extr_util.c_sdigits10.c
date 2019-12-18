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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ LLONG_MAX ; 
 scalar_t__ LLONG_MIN ; 
 scalar_t__ digits10 (scalar_t__) ; 

uint32_t sdigits10(int64_t v) {
    if (v < 0) {
        /* Abs value of LLONG_MIN requires special handling. */
        uint64_t uv = (v != LLONG_MIN) ?
                      (uint64_t)-v : ((uint64_t) LLONG_MAX)+1;
        return digits10(uv)+1; /* +1 for the minus. */
    } else {
        return digits10(v);
    }
}