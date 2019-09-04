#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int /*<<< orphan*/  action; int /*<<< orphan*/  handle; int /*<<< orphan*/  package; } ;
typedef  TYPE_1__ msi_custom_action_info ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  custom_get_thread_return (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_dialog_check_messages (int /*<<< orphan*/ ) ; 
 int msidbCustomActionTypeAsync ; 
 int msidbCustomActionTypeContinue ; 
 int /*<<< orphan*/  release_custom_action_data (TYPE_1__*) ; 

__attribute__((used)) static UINT wait_thread_handle( msi_custom_action_info *info )
{
    UINT rc = ERROR_SUCCESS;

    if (!(info->type & msidbCustomActionTypeAsync))
    {
        TRACE("waiting for %s\n", debugstr_w( info->action ));

        msi_dialog_check_messages( info->handle );

        if (!(info->type & msidbCustomActionTypeContinue))
            rc = custom_get_thread_return( info->package, info->handle );

        release_custom_action_data( info );
    }
    else
    {
        TRACE("%s running in background\n", debugstr_w( info->action ));
    }

    return rc;
}