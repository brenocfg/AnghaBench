#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t* script_actions_count; int /*<<< orphan*/ ** script_actions; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 size_t ACTION_PerformAction (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ERR (char*,size_t,int /*<<< orphan*/ ,size_t) ; 
 size_t ERROR_SUCCESS ; 
 size_t SCRIPT_ROLLBACK ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free_action_script (TYPE_1__*,size_t) ; 

__attribute__((used)) static UINT execute_script( MSIPACKAGE *package, UINT script )
{
    UINT i, rc = ERROR_SUCCESS;

    TRACE("executing script %u\n", script);

    if (script == SCRIPT_ROLLBACK)
    {
        for (i = package->script_actions_count[script]; i > 0; i--)
        {
            rc = ACTION_PerformAction(package, package->script_actions[script][i-1], script);
            if (rc != ERROR_SUCCESS)
            {
                ERR("Execution of script %i halted; action %s returned %u\n",
                    script, debugstr_w(package->script_actions[script][i-1]), rc);
                break;
            }
        }
    }
    else
    {
        for (i = 0; i < package->script_actions_count[script]; i++)
        {
            rc = ACTION_PerformAction(package, package->script_actions[script][i], script);
            if (rc != ERROR_SUCCESS)
            {
                ERR("Execution of script %i halted; action %s returned %u\n",
                    script, debugstr_w(package->script_actions[script][i]), rc);
                break;
            }
        }
    }
    msi_free_action_script(package, script);
    return rc;
}