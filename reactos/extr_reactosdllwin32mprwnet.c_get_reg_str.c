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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static WCHAR *get_reg_str(HKEY hkey, const WCHAR *value, DWORD *len)
{
    DWORD type;
    WCHAR *ret = NULL;

    if (!RegQueryValueExW(hkey, value, NULL, &type, NULL, len) && type == REG_SZ)
    {
        if (!(ret = HeapAlloc(GetProcessHeap(), 0, *len))) return NULL;
        RegQueryValueExW(hkey, value, 0, 0, (BYTE *)ret, len);
    }

    return ret;
}