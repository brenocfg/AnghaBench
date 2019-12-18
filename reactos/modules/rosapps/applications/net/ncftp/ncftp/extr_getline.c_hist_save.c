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
 int /*<<< orphan*/  gl_error (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static char *
hist_save(char *p)

/* makes a copy of the string */
{
    char *s = 0;
    size_t len = strlen(p);
    char *nl = strpbrk(p, "\n\r");

    if (nl) {
        if ((s = (char *) malloc(len)) != 0) {
            strncpy(s, p, len-1);
	    s[len-1] = 0;
	}
    } else {
        if ((s = (char *) malloc(len+1)) != 0) {
            strcpy(s, p);
        }
    }
    if (s == 0)
	gl_error("\n*** Error: hist_save() failed on malloc\n");
    return s;
}