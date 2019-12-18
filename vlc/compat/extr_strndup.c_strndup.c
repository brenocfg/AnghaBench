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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strnlen (char const*,size_t) ; 

char *strndup (const char *str, size_t max)
{
    size_t len = strnlen (str, max);
    char *res = malloc (len + 1);
    if (res)
    {
        memcpy (res, str, len);
        res[len] = '\0';
    }
    return res;
}