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
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int GetBValue (int /*<<< orphan*/ ) ; 
 int GetGValue (int /*<<< orphan*/ ) ; 
 int GetRValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int NUM_SYS_COLORS ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * SysColorsNames ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  strColorKey ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void save_sys_colors (HKEY baseKey)
{
    char colorStr[13];
    HKEY hKey;
    int i;

    if (RegCreateKeyExW( baseKey, strColorKey,
                         0, 0, 0, KEY_ALL_ACCESS,
                         0, &hKey, 0 ) == ERROR_SUCCESS)
    {
        for (i = 0; i < NUM_SYS_COLORS; i++)
        {
            COLORREF col = GetSysColor (i);
        
            sprintf (colorStr, "%d %d %d", 
                GetRValue (col), GetGValue (col), GetBValue (col));

            RegSetValueExA (hKey, SysColorsNames[i], 0, REG_SZ, 
                (BYTE*)colorStr, strlen (colorStr)+1);
        }
        RegCloseKey (hKey);
    }
}