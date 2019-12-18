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
 char* CALL (char* (*) (int),int) ; 
 int /*<<< orphan*/  LOG (char*,char*,int) ; 
 scalar_t__ override ; 

char *strerror (int val)
{
    if (override)
    {
        static const char msg[] =
            "Error message unavailable (use strerror_r instead of strerror)!";
        LOG("Blocked", "%d", val);
        return (char *)msg;
    }
    return CALL(strerror, val);
}