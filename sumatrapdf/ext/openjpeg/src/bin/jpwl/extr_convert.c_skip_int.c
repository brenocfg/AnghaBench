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
 int atoi (char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 char* skip_white (char*) ; 

__attribute__((used)) static char *skip_int(char *start, int *out_n)
{
    char *s;
    char c;

    *out_n = 0;
    s = start;

    s = skip_white(start);
    if (s == NULL) {
        return NULL;
    }
    start = s;

    while (*s) {
        if (!isdigit(*s)) {
            break;
        }
        ++s;
    }
    c = *s;
    *s = 0;
    *out_n = atoi(start);
    *s = c;
    return s;
}