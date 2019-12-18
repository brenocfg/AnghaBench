#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* selectPlaneCb ) (int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  outside_opaque; } ;
typedef  TYPE_1__ vout_display_sys_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool SelectRenderPlane(void *opaque, size_t plane)
{
    vout_display_sys_t *sys = opaque;
    return sys->selectPlaneCb(sys->outside_opaque, plane);
}