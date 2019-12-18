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
 int /*<<< orphan*/  annexb_startcode4 ; 
 scalar_t__ memcmp (void const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
hxxx_extra_isannexb(const void *p_extra, size_t i_extra)
{
    return i_extra == 0
        || (i_extra > 4 && memcmp(p_extra, annexb_startcode4, 4) == 0);
}