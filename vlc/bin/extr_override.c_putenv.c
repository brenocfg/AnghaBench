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
 int CALL (int (*) (char*),char*) ; 
 int /*<<< orphan*/  LOG (char*,char*,char*) ; 
 scalar_t__ override ; 

int putenv (char *str)
{
    if (override)
    {
        LOG("Blocked", "\"%s\"", str);
        return 0;
    }
    return CALL(putenv, str);
}