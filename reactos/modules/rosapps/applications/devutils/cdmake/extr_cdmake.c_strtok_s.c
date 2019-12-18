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
 scalar_t__ strchr (char const*,char) ; 

char* strtok_s(char *str, const char *delim, char **ctx)
{
    if (delim == NULL || ctx == NULL || (str == NULL && *ctx == NULL))
    {
        return NULL;
    }

    if (!str)
        str = *ctx;

    while (*str && strchr(delim, *str))
        str++;
    if (!*str)
    {
        *ctx = str;
        return NULL;
    }

    *ctx = str + 1;
    while (**ctx && !strchr(delim, **ctx))
        (*ctx)++;
    if (**ctx)
        *(*ctx)++ = '\0';

    return str;
}