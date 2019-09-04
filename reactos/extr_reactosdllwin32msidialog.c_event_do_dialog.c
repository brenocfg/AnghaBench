#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  retval; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {TYPE_1__* dialog; } ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  IDOK ; 
 TYPE_1__* dialog_create (TYPE_2__*,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_event_handler ; 
 scalar_t__ dialog_run_message_loop (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_dialog_destroy (TYPE_1__*) ; 

__attribute__((used)) static INT event_do_dialog( MSIPACKAGE *package, const WCHAR *name, msi_dialog *parent, BOOL destroy_modeless )
{
    msi_dialog *dialog;
    UINT r;
    INT retval;

    /* create a new dialog */
    dialog = dialog_create( package, name, parent, dialog_event_handler );
    if (dialog)
    {
        /* kill the current modeless dialog */
        if (destroy_modeless && package->dialog)
        {
            msi_dialog_destroy( package->dialog );
            package->dialog = NULL;
        }

        /* modeless dialogs return an error message */
        r = dialog_run_message_loop( dialog );
        if (r == ERROR_SUCCESS)
        {
            retval = dialog->retval;
            msi_dialog_destroy( dialog );
            return retval;
        }
        else
        {
            package->dialog = dialog;
            return IDOK;
        }
    }
    else return 0;
}