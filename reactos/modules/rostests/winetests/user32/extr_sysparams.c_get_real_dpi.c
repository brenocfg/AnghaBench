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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_CONFIG ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  USER_DEFAULT_SCREEN_DPI ; 
 scalar_t__ get_reg_dword (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD get_real_dpi(void)
{
    DWORD dpi;

    if (get_reg_dword(HKEY_CURRENT_USER, "Control Panel\\Desktop", "LogPixels", &dpi))
        return dpi;
    if (get_reg_dword(HKEY_CURRENT_CONFIG, "Software\\Fonts", "LogPixels", &dpi))
        return dpi;
    return USER_DEFAULT_SCREEN_DPI;
}