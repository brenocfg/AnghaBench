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
struct TYPE_7__ {int dwStyle; } ;
struct TYPE_6__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ REBAR_INFO ;

/* Variables and functions */
 int CCS_VERT ; 

__attribute__((used)) static void translate_rect(const REBAR_INFO *infoPtr, RECT *dest, const RECT *src)
{
    if (infoPtr->dwStyle & CCS_VERT) {
        int tmp;
        tmp = src->left;
        dest->left = src->top;
        dest->top = tmp;
        
        tmp = src->right;
        dest->right = src->bottom;
        dest->bottom = tmp;
    } else {
        *dest = *src;
    }
}