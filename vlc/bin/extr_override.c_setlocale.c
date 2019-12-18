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
 char* CALL (char* (*) (int,char const*),int,char const*) ; 
 int /*<<< orphan*/  LOG (char*,char*,int,char const*) ; 
 scalar_t__ override ; 

char *setlocale (int cat, const char *locale)
{
    if (override && locale != NULL)
    {
        LOG("Blocked", "%d, \"%s\"", cat, locale);
        return NULL;
    }
    return CALL(setlocale, cat, locale);
}