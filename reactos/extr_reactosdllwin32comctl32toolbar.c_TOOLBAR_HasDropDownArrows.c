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
typedef  int BOOL ;

/* Variables and functions */
 int TBSTYLE_EX_DRAWDDARROWS ; 

__attribute__((used)) static inline BOOL TOOLBAR_HasDropDownArrows(DWORD exStyle)
{
    return (exStyle & TBSTYLE_EX_DRAWDDARROWS) != 0;
}