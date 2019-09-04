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
typedef  scalar_t__* LPDWORD ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int REG_DWORD ; 
 int RegQueryValueExW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_dword_from_reg(HKEY hcu, HKEY hklm, LPCWSTR name, LPDWORD out)
{
    DWORD type = REG_DWORD;
    DWORD len = sizeof(DWORD);
    DWORD res;

    res = RegQueryValueExW(hcu, name, NULL, &type, (LPBYTE) out, &len);

    if (res && hklm) {
        len = sizeof(DWORD);
        type = REG_DWORD;
        res = RegQueryValueExW(hklm, name, NULL, &type, (LPBYTE) out, &len);
    }

    if (res) {
        TRACE("%s failed: %d\n", debugstr_w(name), res);
        *out = 0;
    }
}