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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  Connections ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  WinHttpSettings ; 

__attribute__((used)) static DWORD get_default_proxy_reg_value( BYTE *buf, DWORD len, DWORD *type )
{
    LONG l;
    HKEY key;
    DWORD ret = 0;

    l = RegOpenKeyExW( HKEY_LOCAL_MACHINE, Connections, 0, KEY_READ, &key );
    if (!l)
    {
        DWORD size = 0;

        l = RegQueryValueExW( key, WinHttpSettings, NULL, type, NULL, &size );
        if (!l)
        {
            if (size <= len)
                l = RegQueryValueExW( key, WinHttpSettings, NULL, type, buf,
                    &size );
            if (!l)
                ret = size;
        }
        RegCloseKey( key );
    }
    return ret;
}