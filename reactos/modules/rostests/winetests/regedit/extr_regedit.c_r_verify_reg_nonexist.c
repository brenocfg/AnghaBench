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
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lok (int,char*,char const*,scalar_t__) ; 

__attribute__((used)) static void r_verify_reg_nonexist(unsigned line, HKEY key, const char *value_name)
{
    LONG lr;

    lr = RegQueryValueExA(key, value_name, NULL, NULL, NULL, NULL);
    lok(lr == ERROR_FILE_NOT_FOUND, "registry value '%s' shouldn't exist; got %d, expected 2\n",
       (value_name && *value_name) ? value_name : "(Default)", lr);
}