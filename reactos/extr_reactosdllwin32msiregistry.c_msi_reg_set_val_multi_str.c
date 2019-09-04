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
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MULTI_SZ ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ lstrlenW (scalar_t__*) ; 

LONG msi_reg_set_val_multi_str( HKEY hkey, LPCWSTR name, LPCWSTR value )
{
    LPCWSTR p = value;
    while (*p) p += lstrlenW(p) + 1;
    return RegSetValueExW( hkey, name, 0, REG_MULTI_SZ,
                           (const BYTE *)value, (p + 1 - value) * sizeof(WCHAR) );
}