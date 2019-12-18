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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _errno () ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static inline BOOL strftime_str(char *str, size_t *pos, size_t max, char *src)
{
    size_t len = strlen(src);
    if(len > max-*pos) {
        *str = 0;
        *_errno() = ERANGE;
        return FALSE;
    }

    memcpy(str+*pos, src, len);
    *pos += len;
    return TRUE;
}