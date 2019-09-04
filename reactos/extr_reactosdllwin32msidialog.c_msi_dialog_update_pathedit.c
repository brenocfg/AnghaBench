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
typedef  int /*<<< orphan*/  msi_dialog ;
struct TYPE_4__ {int attributes; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  property; } ;
typedef  TYPE_1__ msi_control ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  msi_dialog_dup_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* msi_dialog_find_control_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 int msidbControlAttributesIndirect ; 
 int /*<<< orphan*/  szPathEdit ; 

__attribute__((used)) static void msi_dialog_update_pathedit( msi_dialog *dialog, msi_control *control )
{
    LPWSTR prop, path;
    BOOL indirect;

    if (!control && !(control = msi_dialog_find_control_by_type( dialog, szPathEdit )))
       return;

    indirect = control->attributes & msidbControlAttributesIndirect;
    prop = msi_dialog_dup_property( dialog, control->property, indirect );
    path = msi_dialog_dup_property( dialog, prop, TRUE );

    SetWindowTextW( control->hwnd, path );
    SendMessageW( control->hwnd, EM_SETSEL, 0, -1 );

    msi_free( path );
    msi_free( prop );
}