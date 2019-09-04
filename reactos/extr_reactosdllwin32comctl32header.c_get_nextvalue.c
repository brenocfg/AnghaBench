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
typedef  scalar_t__ INT ;

/* Variables and functions */
 int has_duplicate (scalar_t__ const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static INT get_nextvalue(const INT *array, INT to, INT max)
{
    INT i;
    for(i = 0; i < max; i++)
        if (has_duplicate(array, to, i) == -1) return i;
    return 0;
}