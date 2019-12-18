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
typedef  scalar_t__ UInt64 ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */

__attribute__((used)) static int _chm_parse_UTF8(UChar **pEntry, UInt64 count, char *path)
{
    /* XXX: implement UTF-8 support, including a real mapping onto
     *      ISO-8859-1?  probably there is a library to do this?  As is
     *      immediately apparent from the below code, I'm presently not doing
     *      any special handling for files in which none of the strings contain
     *      UTF-8 multi-byte characters.
     */
    while (count != 0)
    {
        *path++ = (char)(*(*pEntry)++);
        --count;
    }

    *path = '\0';
    return 1;
}