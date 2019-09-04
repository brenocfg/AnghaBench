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
 int CE_NAMEMASK ; 
 int CE_STAGEMASK ; 
 int memcmp (char const*,char const*,int) ; 

int cache_name_compare(const char *name1, int flags1, const char *name2, int flags2)
{
    int len1 = flags1 & CE_NAMEMASK;
    int len2 = flags2 & CE_NAMEMASK;
    int len = len1 < len2 ? len1 : len2;
    int cmp;

    cmp = memcmp(name1, name2, len);
    if (cmp)
        return cmp;
    if (len1 < len2)
        return -1;
    if (len1 > len2)
        return 1;

    /* Compare stages  */
    flags1 &= CE_STAGEMASK;
    flags2 &= CE_STAGEMASK;

    if (flags1 < flags2)
        return -1;
    if (flags1 > flags2)
        return 1;
    return 0;
}