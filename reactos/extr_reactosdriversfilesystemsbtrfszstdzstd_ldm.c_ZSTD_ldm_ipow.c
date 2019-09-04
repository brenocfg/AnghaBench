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
typedef  int U64 ;

/* Variables and functions */

__attribute__((used)) static U64 ZSTD_ldm_ipow(U64 base, U64 exp)
{
    U64 ret = 1;
    while (exp) {
        if (exp & 1) { ret *= base; }
        exp >>= 1;
        base *= base;
    }
    return ret;
}