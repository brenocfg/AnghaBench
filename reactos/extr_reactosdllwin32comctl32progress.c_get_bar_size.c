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
struct TYPE_3__ {int bottom; int top; int right; int left; } ;
typedef  TYPE_1__ RECT ;
typedef  int LONG ;

/* Variables and functions */
 int PBS_VERTICAL ; 

__attribute__((used)) static inline int get_bar_size( LONG style, const RECT* rect )
{
    if (style & PBS_VERTICAL)
        return rect->bottom - rect->top;
    else
        return rect->right - rect->left;
}