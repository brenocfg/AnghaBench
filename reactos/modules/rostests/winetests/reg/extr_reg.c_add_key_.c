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

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/  const,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lok (int,char*,scalar_t__) ; 

__attribute__((used)) static void add_key_(unsigned line, const HKEY hkey, const char *path, HKEY *subkey)
{
    LONG err;

    err = RegCreateKeyExA(hkey, path, 0, NULL, REG_OPTION_NON_VOLATILE,
                          KEY_READ|KEY_WRITE, NULL, subkey, NULL);
    lok(err == ERROR_SUCCESS, "RegCreateKeyExA failed: %d\n", err);
}