#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_5__ {scalar_t__ off_bitmap; scalar_t__ off_dc; } ;
typedef  TYPE_2__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 

__attribute__((used)) static void Clean(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    if (sys->off_dc)
        DeleteDC(sys->off_dc);
    if (sys->off_bitmap)
        DeleteObject(sys->off_bitmap);
}