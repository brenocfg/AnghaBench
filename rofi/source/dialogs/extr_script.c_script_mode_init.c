#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ed; int /*<<< orphan*/ * private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  cmd_list_length; int /*<<< orphan*/  cmd_list; } ;
typedef  TYPE_1__ ScriptModePrivateData ;
typedef  TYPE_2__ Mode ;

/* Variables and functions */
 int TRUE ; 
 TYPE_1__* g_malloc0 (int) ; 
 int /*<<< orphan*/  get_script_output (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int script_mode_init ( Mode *sw )
{
    if ( sw->private_data == NULL ) {
        ScriptModePrivateData *pd = g_malloc0 ( sizeof ( *pd ) );
        sw->private_data = (void *) pd;
        pd->cmd_list     = get_script_output ( sw, (char *) sw->ed, NULL, &( pd->cmd_list_length ) );
    }
    return TRUE;
}