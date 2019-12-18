#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ w; scalar_t__ h; } ;
typedef  TYPE_1__ spu_scale_t ;
struct TYPE_11__ {TYPE_1__ scale; void* height; void* width; void* y; void* x; } ;
typedef  TYPE_2__ spu_area_t ;

/* Variables and functions */
 TYPE_2__ spu_area_scaled (TYPE_2__) ; 
 void* spu_invscale_h (void*,TYPE_1__) ; 
 void* spu_invscale_w (void*,TYPE_1__) ; 

__attribute__((used)) static spu_area_t spu_area_unscaled(spu_area_t a, spu_scale_t s)
{
    if (a.scale.w == s.w && a.scale.h == s.h)
        return a;

    a = spu_area_scaled(a);

    a.x      = spu_invscale_w(a.x,      s);
    a.y      = spu_invscale_h(a.y,      s);
    a.width  = spu_invscale_w(a.width,  s);
    a.height = spu_invscale_h(a.height, s);

    a.scale = s;
    return a;
}