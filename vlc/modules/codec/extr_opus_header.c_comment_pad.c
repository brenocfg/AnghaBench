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
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static int comment_pad(char **comments, size_t *length)
{
    const unsigned padding = 512; /* default from opus-tools */

    if(SIZE_MAX - *length < padding + 255)
        return 1;

    char *p = *comments;
    /* Make sure there is at least "padding" worth of padding free, and
       round up to the maximum that fits in the current ogg segments. */
    size_t newlen = ((*length + padding) / 255 + 1) * 255 - 1;
    char *reaced = realloc(p, newlen);
    if (reaced == NULL)
        return 1;
    p = reaced;

    memset(p + *length, 0, newlen - *length);
    *comments = p;
    *length = newlen;
    return 0;
}