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
 scalar_t__ ag_malloc (size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

char *ag_strndup(const char *s, size_t size) {
    char *str = NULL;
#ifdef HAVE_STRNDUP
    str = strndup(s, size);
    CHECK_AND_RETURN(str)
#else
    str = (char *)ag_malloc(size + 1);
    strlcpy(str, s, size + 1);
    return str;
#endif
}