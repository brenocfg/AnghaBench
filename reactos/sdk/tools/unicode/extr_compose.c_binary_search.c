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
typedef  scalar_t__ WCHAR ;

/* Variables and functions */
 scalar_t__* table ; 

__attribute__((used)) static inline int binary_search( WCHAR ch, int low, int high )
{
    while (low <= high)
    {
        int pos = (low + high) / 2;
        if (table[2 * pos] < ch) low = pos + 1;
        else if (table[2 * pos] > ch) high = pos - 1;
        else return pos;
    }
    return -1;
}