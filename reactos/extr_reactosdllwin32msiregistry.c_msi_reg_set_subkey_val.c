#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ msi_reg_set_val_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

LONG msi_reg_set_subkey_val( HKEY hkey, LPCWSTR path, LPCWSTR name, LPCWSTR val )
{
    HKEY hsubkey = 0;
    LONG r;

    r = RegCreateKeyW( hkey, path, &hsubkey );
    if (r != ERROR_SUCCESS)
        return r;
    r = msi_reg_set_val_str( hsubkey, name, val );
    RegCloseKey( hsubkey );
    return r;
}