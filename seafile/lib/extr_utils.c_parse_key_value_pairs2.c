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
typedef  scalar_t__ (* KeyValueFunc2 ) (void*,char*,char*) ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  g_warning (char*,char*) ; 

void parse_key_value_pairs2 (char *string, KeyValueFunc2 func, void *data)
{
    char *line = string, *next, *space;
    char *key, *value;

    while (*line) {
        /* handle empty line */
        if (*line == '\n') {
            ++line;
            continue;
        }

        for (next = line; *next != '\n' && *next; ++next) ;
        *next = '\0';
        
        for (space = line; space < next && *space != ' '; ++space) ;
        if (*space != ' ') {
            g_warning ("Bad key value format: %s\n", line);
            return;
        }
        *space = '\0';
        key = line;
        value = space + 1;
        
        if (func(data, key, value) == FALSE)
            break;

        line = next + 1;
    }
}