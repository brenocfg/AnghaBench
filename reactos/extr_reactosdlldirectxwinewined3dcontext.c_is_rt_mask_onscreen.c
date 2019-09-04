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
typedef  unsigned int DWORD ;
typedef  unsigned int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL is_rt_mask_onscreen(DWORD rt_mask)
{
    return rt_mask & (1u << 31);
}