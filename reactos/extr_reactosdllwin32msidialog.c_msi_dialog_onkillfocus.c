#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  package; } ;
typedef  TYPE_1__ msi_dialog ;
struct TYPE_9__ {int attributes; int /*<<< orphan*/  name; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  property; } ;
typedef  TYPE_2__ msi_control ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_dialog_dup_property (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msi_dialog_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_dialog_update_pathedit (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_dialog_verify_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_get_window_text (int /*<<< orphan*/ ) ; 
 int msidbControlAttributesIndirect ; 

__attribute__((used)) static BOOL msi_dialog_onkillfocus( msi_dialog *dialog, msi_control *control )
{
    LPWSTR buf, prop;
    BOOL indirect;
    BOOL valid;

    indirect = control->attributes & msidbControlAttributesIndirect;
    prop = msi_dialog_dup_property( dialog, control->property, indirect );

    buf = msi_get_window_text( control->hwnd );

    if ( !msi_dialog_verify_path( buf ) )
    {
        /* FIXME: display an error message box */
        ERR("Invalid path %s\n", debugstr_w( buf ));
        valid = FALSE;
        SetFocus( control->hwnd );
    }
    else
    {
        valid = TRUE;
        msi_dialog_set_property( dialog->package, prop, buf );
    }

    msi_dialog_update_pathedit( dialog, control );

    TRACE("edit %s contents changed, set %s\n", debugstr_w(control->name),
          debugstr_w(prop));

    msi_free( buf );
    msi_free( prop );

    return valid;
}