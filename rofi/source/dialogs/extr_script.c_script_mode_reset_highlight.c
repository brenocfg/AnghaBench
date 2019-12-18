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
struct TYPE_5__ {scalar_t__ private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * active_list; scalar_t__ num_active_list; int /*<<< orphan*/ * urgent_list; scalar_t__ num_urgent_list; } ;
typedef  TYPE_1__ ScriptModePrivateData ;
typedef  TYPE_2__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script_mode_reset_highlight ( Mode *sw )
{
    ScriptModePrivateData *rmpd = (ScriptModePrivateData *) sw->private_data;

    rmpd->num_urgent_list = 0;
    g_free ( rmpd->urgent_list );
    rmpd->urgent_list     = NULL;
    rmpd->num_active_list = 0;
    g_free ( rmpd->active_list );
    rmpd->active_list = NULL;
}