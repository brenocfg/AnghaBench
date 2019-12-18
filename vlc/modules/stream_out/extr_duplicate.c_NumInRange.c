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
 int sscanf (char const*,char*,int*,int*) ; 

__attribute__((used)) static bool NumInRange( const char *psz_range, int i_num )
{
    int beginRange, endRange;
    int res = sscanf(psz_range, "%d-%d", &beginRange, &endRange);
    if (res == 0)
        return false;
    else if (res == 1)
        return beginRange == i_num;
    return (i_num >= beginRange && i_num <= endRange)
        || (beginRange > endRange && (i_num <= beginRange && i_num >= endRange));
}