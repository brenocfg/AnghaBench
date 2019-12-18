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
typedef  int /*<<< orphan*/  cmsUInt32Number ;

/* Variables and functions */
 size_t T_BYTES (int /*<<< orphan*/ ) ; 
 size_t T_CHANNELS (int /*<<< orphan*/ ) ; 
 size_t T_EXTRA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
size_t PixelSize(cmsUInt32Number dwFormat)
{
    return T_BYTES(dwFormat) * (T_CHANNELS(dwFormat) + T_EXTRA(dwFormat));
}