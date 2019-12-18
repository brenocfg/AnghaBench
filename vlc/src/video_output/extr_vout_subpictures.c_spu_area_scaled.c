#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ w; scalar_t__ h; } ;
struct TYPE_7__ {TYPE_2__ scale; void* height; void* width; void* y; void* x; } ;
typedef  TYPE_1__ spu_area_t ;

/* Variables and functions */
 scalar_t__ SCALE_UNIT ; 
 void* spu_scale_h (void*,TYPE_2__) ; 
 TYPE_2__ spu_scale_unit () ; 
 void* spu_scale_w (void*,TYPE_2__) ; 

__attribute__((used)) static spu_area_t spu_area_scaled(spu_area_t a)
{
    if (a.scale.w == SCALE_UNIT && a.scale.h == SCALE_UNIT)
        return a;

    a.x      = spu_scale_w(a.x,      a.scale);
    a.y      = spu_scale_h(a.y,      a.scale);
    a.width  = spu_scale_w(a.width,  a.scale);
    a.height = spu_scale_h(a.height, a.scale);

    a.scale = spu_scale_unit();
    return a;
}