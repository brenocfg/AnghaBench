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
typedef  enum platform { ____Placeholder_platform } platform ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int PLATFORM_INTEL ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_64bit ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szUninstall ; 
 int /*<<< orphan*/  szUninstall_32node ; 

UINT MSIREG_OpenUninstallKey(const WCHAR *product, enum platform platform, HKEY *key, BOOL create)
{
    WCHAR keypath[0x200];

    TRACE("%s\n", debugstr_w(product));

    if (is_64bit && platform == PLATFORM_INTEL)
    {
        strcpyW(keypath, szUninstall_32node);
        strcatW(keypath, product);
    }
    else
    {
        strcpyW(keypath, szUninstall);
        strcatW(keypath, product);
    }
    if (create) return RegCreateKeyExW(HKEY_LOCAL_MACHINE, keypath, 0, NULL, 0, KEY_ALL_ACCESS, NULL, key, NULL);
    return RegOpenKeyExW(HKEY_LOCAL_MACHINE, keypath, 0, KEY_ALL_ACCESS, key);
}