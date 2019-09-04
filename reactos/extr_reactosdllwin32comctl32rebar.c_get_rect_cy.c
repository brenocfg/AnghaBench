#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dwStyle; } ;
struct TYPE_5__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ REBAR_INFO ;

/* Variables and functions */
 int CCS_VERT ; 

__attribute__((used)) static int get_rect_cy(const REBAR_INFO *infoPtr, const RECT *lpRect)
{
    if (infoPtr->dwStyle & CCS_VERT)
        return lpRect->right - lpRect->left;
    return lpRect->bottom - lpRect->top;
}