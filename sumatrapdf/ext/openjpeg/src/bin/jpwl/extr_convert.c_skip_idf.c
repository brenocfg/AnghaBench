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
 scalar_t__ isalpha (char) ; 
 char* skip_white (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static char *skip_idf(char *start, char out_idf[256])
{
    char *s;
    char c;

    s = skip_white(start);
    if (s == NULL) {
        return NULL;
    }
    start = s;

    while (*s) {
        if (isalpha(*s) || *s == '_') {
            ++s;
            continue;
        }
        break;
    }
    c = *s;
    *s = 0;
    strncpy(out_idf, start, 255);
    *s = c;
    return s;
}