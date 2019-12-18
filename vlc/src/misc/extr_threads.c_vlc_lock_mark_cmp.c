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
struct vlc_lock_mark {scalar_t__ object; } ;

/* Variables and functions */

__attribute__((used)) static int vlc_lock_mark_cmp(const void *a, const void *b)
{
    const struct vlc_lock_mark *ma = a, *mb = b;

    if (ma->object == mb->object)
        return 0;

    return ((uintptr_t)(ma->object) > (uintptr_t)(mb->object)) ? +1 : -1;
}