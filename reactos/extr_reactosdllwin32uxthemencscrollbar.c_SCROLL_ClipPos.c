#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ left; scalar_t__ right; scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_6__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__* LPRECT ;

/* Variables and functions */

__attribute__((used)) static POINT SCROLL_ClipPos( LPRECT lpRect, POINT pt )
{
    if( pt.x < lpRect->left )
	    pt.x = lpRect->left;
    else
        if( pt.x > lpRect->right )
	pt.x = lpRect->right;

    if( pt.y < lpRect->top )
	    pt.y = lpRect->top;
    else
    if( pt.y > lpRect->bottom )
	    pt.y = lpRect->bottom;

    return pt;
}