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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ action_progress_increment; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 scalar_t__ ACTION_HandleCustomAction (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ACTION_HandleStandardAction (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ ERROR_FUNCTION_NOT_CALLED ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 

UINT ACTION_PerformAction(MSIPACKAGE *package, const WCHAR *action, UINT script)
{
    UINT rc;

    TRACE("Performing action (%s)\n", debugstr_w(action));

    package->action_progress_increment = 0;
    rc = ACTION_HandleStandardAction(package, action);

    if (rc == ERROR_FUNCTION_NOT_CALLED)
        rc = ACTION_HandleCustomAction(package, action, script);

    if (rc == ERROR_FUNCTION_NOT_CALLED)
        WARN("unhandled msi action %s\n", debugstr_w(action));

    return rc;
}