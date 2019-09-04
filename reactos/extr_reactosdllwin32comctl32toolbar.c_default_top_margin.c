#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwStyle; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;

/* Variables and functions */
 int TBSTYLE_FLAT ; 
 int TOP_BORDER ; 

__attribute__((used)) static inline int default_top_margin(const TOOLBAR_INFO *infoPtr)
{
#ifdef __REACTOS__
    if (infoPtr->iVersion == 6)
        return infoPtr->szBarPadding.cy;
#endif
    return (infoPtr->dwStyle & TBSTYLE_FLAT ? 0 : TOP_BORDER);
}