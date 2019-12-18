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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int atoi (char*) ; 

__attribute__((used)) static int get_shell_icon_size(void)
{
    char buf[10];
    DWORD value = 32, size = sizeof(buf), type;
    HKEY key;

    if (!RegOpenKeyA( HKEY_CURRENT_USER, "Control Panel\\Desktop\\WindowMetrics", &key ))
    {
        if (!RegQueryValueExA( key, "Shell Icon Size", NULL, &type, (BYTE *)buf, &size ) && type == REG_SZ)
            value = atoi( buf );
        RegCloseKey( key );
    }
    return value;
}