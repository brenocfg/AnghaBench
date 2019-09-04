#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msi_dialog ;
struct TYPE_3__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ msi_control ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int GetLogicalDriveStringsW (int,scalar_t__*) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrlenW (scalar_t__*) ; 
 scalar_t__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 

__attribute__((used)) static void msi_dialog_vsc_add_drives( msi_dialog *dialog, msi_control *control )
{
    LPWSTR drives, ptr;
    DWORD size;

    size = GetLogicalDriveStringsW( 0, NULL );
    if ( !size ) return;

    drives = msi_alloc( (size + 1) * sizeof(WCHAR) );
    if ( !drives ) return;

    GetLogicalDriveStringsW( size, drives );

    ptr = drives;
    while (*ptr)
    {
        SendMessageW( control->hwnd, CB_ADDSTRING, 0, (LPARAM)ptr );
        ptr += lstrlenW(ptr) + 1;
    }

    msi_free( drives );
}