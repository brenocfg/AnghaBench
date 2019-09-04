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
struct TYPE_2__ {scalar_t__ wm_nextdlgctl; scalar_t__ wm_getdefid; scalar_t__ wm_close; scalar_t__ wm_command; } ;

/* Variables and functions */
 TYPE_1__ dm_messages ; 

__attribute__((used)) static void zero_dm_messages(void)
{
    dm_messages.wm_command      = 0;
    dm_messages.wm_close        = 0;
    dm_messages.wm_getdefid     = 0;
    dm_messages.wm_nextdlgctl   = 0;
}