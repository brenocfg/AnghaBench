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
typedef  int long_u ;

/* Variables and functions */
 int _go32_dpmi_remaining_virtual_memory () ; 
 int coreleft () ; 

long_u
mch_avail_mem(int special)
{
#ifdef DJGPP
    return _go32_dpmi_remaining_virtual_memory() >> 10;
#else
    return coreleft() >> 10;
#endif
}