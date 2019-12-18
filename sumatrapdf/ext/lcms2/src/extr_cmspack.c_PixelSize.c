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
typedef  int /*<<< orphan*/  cmsUInt64Number ;
typedef  scalar_t__ cmsUInt32Number ;

/* Variables and functions */
 scalar_t__ T_BYTES (scalar_t__) ; 

__attribute__((used)) static
cmsUInt32Number PixelSize(cmsUInt32Number Format)
{
    cmsUInt32Number fmt_bytes = T_BYTES(Format);

    // For double, the T_BYTES field is zero
    if (fmt_bytes == 0)
        return sizeof(cmsUInt64Number);

    // Otherwise, it is already correct for all formats
    return fmt_bytes;
}