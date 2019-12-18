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
 void* xmlFileOpen_real (char const*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 char* xmlURIUnescapeString (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *
xmlFileOpen (const char *filename) {
    char *unescaped;
    void *retval;

    retval = xmlFileOpen_real(filename);
    if (retval == NULL) {
	unescaped = xmlURIUnescapeString(filename, 0, NULL);
	if (unescaped != NULL) {
	    retval = xmlFileOpen_real(unescaped);
	    xmlFree(unescaped);
	}
    }

    return retval;
}