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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__* msi_alloc (int) ; 

LPWSTR msi_reg_get_val_str( HKEY hkey, LPCWSTR name )
{
    DWORD len = 0;
    LPWSTR val;
    LONG r;

    r = RegQueryValueExW(hkey, name, NULL, NULL, NULL, &len);
    if (r != ERROR_SUCCESS)
        return NULL;

    len += sizeof (WCHAR);
    val = msi_alloc( len );
    if (!val)
        return NULL;
    val[0] = 0;
    RegQueryValueExW(hkey, name, NULL, NULL, (LPBYTE) val, &len);
    return val;
}