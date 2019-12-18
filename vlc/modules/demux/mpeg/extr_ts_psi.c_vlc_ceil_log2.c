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
 int clz (unsigned int const) ; 

__attribute__((used)) static int vlc_ceil_log2( const unsigned int val )
{
    int n = 31 - clz(val);
    if ((1U << n) != val)
        n++;

    return n;
}