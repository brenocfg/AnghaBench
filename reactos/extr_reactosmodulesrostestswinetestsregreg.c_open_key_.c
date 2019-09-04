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
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int const KEY_READ ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/  const,char const*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lok (int,char*,scalar_t__) ; 

__attribute__((used)) static void open_key_(unsigned line, const HKEY base, const char *path, const DWORD sam, HKEY *hkey)
{
    LONG err;

    err = RegOpenKeyExA(base, path, 0, KEY_READ|sam, hkey);
    lok(err == ERROR_SUCCESS, "RegOpenKeyExA failed: %d\n", err);
}