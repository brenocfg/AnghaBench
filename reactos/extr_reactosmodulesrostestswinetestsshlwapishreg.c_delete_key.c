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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SHDeleteKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD delete_key( HKEY hkey, LPCSTR parent, LPCSTR keyname )
{
    HKEY parentKey;
    DWORD ret;

    RegCloseKey(hkey);

    /* open the parent of the key to close */
    ret = RegOpenKeyExA( HKEY_CURRENT_USER, parent, 0, KEY_ALL_ACCESS, &parentKey);
    if (ret != ERROR_SUCCESS)
        return ret;

    ret = SHDeleteKeyA( parentKey, keyname );
    RegCloseKey(parentKey);

    return ret;
}