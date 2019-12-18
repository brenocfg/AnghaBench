#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* p_sys; } ;
struct TYPE_7__ {TYPE_1__ updater; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_8__ {struct TYPE_8__* text; } ;
typedef  TYPE_3__ osd_spu_updater_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void OSDTextDestroy(subpicture_t *subpic)
{
    osd_spu_updater_sys_t *sys = subpic->updater.p_sys;

    free(sys->text);
    free(sys);
}