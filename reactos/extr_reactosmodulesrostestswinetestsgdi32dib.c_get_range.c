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
typedef  int DWORD ;
typedef  size_t BYTE ;

/* Variables and functions */
 int* ramp ; 

__attribute__((used)) static inline void get_range(BYTE alpha, DWORD text_comp, BYTE *min_comp, BYTE *max_comp)
{
    *min_comp = (ramp[alpha] * text_comp) / 0xff;
    *max_comp = ramp[16 - alpha] + ((0xff - ramp[16 - alpha]) * text_comp) / 0xff;
}