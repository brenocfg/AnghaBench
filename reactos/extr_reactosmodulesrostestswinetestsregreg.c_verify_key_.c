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
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKeyExA (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  lok (int,char*,scalar_t__) ; 

__attribute__((used)) static void verify_key_(unsigned line, HKEY key_base, const char *subkey)
{
    HKEY hkey;
    LONG err;

    err = RegOpenKeyExA(key_base, subkey, 0, KEY_READ, &hkey);
    lok(err == ERROR_SUCCESS, "RegOpenKeyExA failed: got %d\n", err);

    if (hkey)
        RegCloseKey(hkey);
}