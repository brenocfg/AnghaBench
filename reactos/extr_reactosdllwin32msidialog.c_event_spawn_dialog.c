#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ retval; int /*<<< orphan*/  package; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ event_do_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_dialog_end_dialog (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_dialog_update_all_controls (TYPE_1__*) ; 

__attribute__((used)) static UINT event_spawn_dialog( msi_dialog *dialog, const WCHAR *argument )
{
    INT r;
    /* don't destroy a modeless dialogs that might be our parent */
    r = event_do_dialog( dialog->package, argument, dialog, FALSE );
    if (r != 0)
    {
        dialog->retval = r;
        msi_dialog_end_dialog( dialog );
    }
    else
        msi_dialog_update_all_controls(dialog);

    return ERROR_SUCCESS;
}