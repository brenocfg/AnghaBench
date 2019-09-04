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
typedef  int /*<<< orphan*/  REGSAM ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  Connections ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WinHttpSettings ; 

__attribute__((used)) static void set_proxy( REGSAM access, BYTE *buf, DWORD len, DWORD type )
{
    HKEY hkey;
    if (!RegCreateKeyExW( HKEY_LOCAL_MACHINE, Connections, 0, NULL, 0, access, NULL, &hkey, NULL ))
    {
        if (len) RegSetValueExW( hkey, WinHttpSettings, 0, type, buf, len );
        else RegDeleteValueW( hkey, WinHttpSettings );
        RegCloseKey( hkey );
    }
}