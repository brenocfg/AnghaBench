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
typedef  size_t UINT_PTR ;
typedef  size_t UINT ;
typedef  scalar_t__ HICON ;

/* Variables and functions */
 size_t TTI_ERROR ; 
 scalar_t__* hTooltipIcons ; 

__attribute__((used)) static inline UINT_PTR
TOOLTIPS_GetTitleIconIndex(HICON hIcon)
{
    UINT i;
    for (i = 0; i <= TTI_ERROR; i++)
        if (hTooltipIcons[i] == hIcon)
            return i;
    return (UINT_PTR)hIcon;
}