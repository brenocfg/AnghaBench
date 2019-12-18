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
struct TYPE_3__ {void* yMax; void* xMax; void* yMin; void* xMin; } ;
typedef  TYPE_1__ FT_BBox ;

/* Variables and functions */
 void* INT_MAX ; 
 void* INT_MIN ; 

__attribute__((used)) static inline void BBoxInit( FT_BBox *p_box )
{
    p_box->xMin = INT_MAX;
    p_box->yMin = INT_MAX;
    p_box->xMax = INT_MIN;
    p_box->yMax = INT_MIN;
}