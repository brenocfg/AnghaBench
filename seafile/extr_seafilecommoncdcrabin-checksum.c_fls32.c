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
typedef  int u_int32_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__* bytemsb ; 

__attribute__((used)) static inline u_int fls32 (u_int32_t v)
{
    if (v & 0xffff0000) {
        if (v & 0xff000000)
            return 24 + bytemsb[v>>24];
        else
            return 16 + bytemsb[v>>16];
    }
    if (v & 0x0000ff00)
        return 8 + bytemsb[v>>8];
    else
        return bytemsb[v];
}