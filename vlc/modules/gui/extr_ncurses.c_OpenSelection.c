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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_6__ {int plidx_follow; int /*<<< orphan*/  open_chain; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddItem (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OpenSelection(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;

    AddItem(intf, sys->open_chain);
    sys->plidx_follow = true;
}