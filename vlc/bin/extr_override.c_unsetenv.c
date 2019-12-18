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
 int CALL (int (*) (char const*),char const*) ; 
 int /*<<< orphan*/  LOG (char*,char*,char const*) ; 
 scalar_t__ override ; 

int unsetenv (const char *name)
{
    if (override)
    {
        LOG("Blocked", "\"%s\"", name);
        return 0;
    }
    return CALL(unsetenv, name);
}