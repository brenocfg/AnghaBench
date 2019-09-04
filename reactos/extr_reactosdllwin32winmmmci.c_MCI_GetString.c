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
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MCIERR_EXTRA_CHARACTERS ; 
 int /*<<< orphan*/  MCIERR_NO_CLOSING_QUOTE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 char* strchrW (char*,char) ; 
 int strlenW (char*) ; 

__attribute__((used)) static	DWORD	MCI_GetString(LPWSTR* str, LPWSTR* args)
{
    LPWSTR      ptr = *args;

    /* see if we have a quoted string */
    if (*ptr == '"') {
	ptr = strchrW(*str = ptr + 1, '"');
	if (!ptr) return MCIERR_NO_CLOSING_QUOTE;
	/* FIXME: shall we escape \" from string ?? */
	if (ptr[-1] == '\\') TRACE("Ooops: un-escaped \"\n");
	*ptr++ = '\0'; /* remove trailing " */
	if (*ptr != ' ' && *ptr != '\0') return MCIERR_EXTRA_CHARACTERS;
    } else {
	ptr = strchrW(ptr, ' ');

	if (ptr) {
	    *ptr++ = '\0';
	} else {
	    ptr = *args + strlenW(*args);
	}
	*str = *args;
    }

    *args = ptr;
    return 0;
}