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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int MAX_PATH ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL check_reg_str(HKEY hkey, LPCSTR name, LPCSTR value)
{
    DWORD size = MAX_PATH;
    char check[MAX_PATH];

    if (RegQueryValueExA(hkey, name, NULL, NULL, (LPBYTE)check, &size))
        return FALSE;

    return !lstrcmpA(check, value);
}