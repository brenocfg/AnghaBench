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

/* Variables and functions */
 scalar_t__ ERROR_ENVVAR_NOT_FOUND ; 
 scalar_t__ GetEnvironmentVariableA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char*) ; 

void silence_debug_output(void)
{
    if (GetEnvironmentVariableA("SHIM_DEBUG_LEVEL", NULL, 0) == ERROR_ENVVAR_NOT_FOUND)
        SetEnvironmentVariableA("SHIM_DEBUG_LEVEL", "0");
    if (GetEnvironmentVariableA("SHIMENG_DEBUG_LEVEL", NULL, 0) == ERROR_ENVVAR_NOT_FOUND)
        SetEnvironmentVariableA("SHIMENG_DEBUG_LEVEL", "0");
}