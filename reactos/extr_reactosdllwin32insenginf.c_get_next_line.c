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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 char* trim (char*,char**,scalar_t__) ; 

__attribute__((used)) static char *get_next_line(char **str, char **last_chr)
{
    BOOL in_next_line = FALSE;
    char *start, *next;

    start = *str;
    if (!start || !*start) return NULL;

    for (next = start; *next; next++)
    {
        if (*next == '\n' || *next == '\r')
        {
            *next = 0;
            in_next_line = TRUE;
        }
        else if (in_next_line)
        {
            break;
        }
    }

    *str = next;
    return trim(start, last_chr, FALSE);
}