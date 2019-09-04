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
 size_t ABS_TRESHOLD ; 

size_t
fixup_offset(size_t ImageBase, size_t offset)
{
    if (offset > ABS_TRESHOLD)
        offset -= ImageBase;
    return offset;
}