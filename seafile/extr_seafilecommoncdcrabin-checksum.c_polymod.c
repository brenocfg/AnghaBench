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
typedef  int u_int64_t ;

/* Variables and functions */
 int INT64 (int) ; 
 int MSB64 ; 
 int fls64 (int) ; 

u_int64_t polymod (u_int64_t nh, u_int64_t nl, u_int64_t d)
{
    int i = 0;
    int k = fls64 (d) - 1;

    d <<= 63 - k;

    if (nh) {
        if (nh & MSB64)
            nh ^= d;
        for (i = 62; i >= 0; i--)
            if (nh & ((u_int64_t) 1) << i) {
                nh ^= d >> (63 - i);
                nl ^= d << (i + 1);
            }
    }
    for (i = 63; i >= k; i--)
    {  
        if (nl & INT64 (1) << i)
            nl ^= d >> (63 - i);
    }
  
    return nl;
}