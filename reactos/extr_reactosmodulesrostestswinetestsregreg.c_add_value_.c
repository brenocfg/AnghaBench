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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  lok (int,char*,scalar_t__) ; 

__attribute__((used)) static void add_value_(unsigned line, HKEY hkey, const char *name, DWORD type,
                       const void *data, size_t size)
{
    LONG err;

    err = RegSetValueExA(hkey, name, 0, type, (const BYTE *)data, size);
    lok(err == ERROR_SUCCESS, "RegSetValueExA failed: %d\n", err);
}