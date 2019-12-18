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
 int EINVAL ; 

__attribute__((used)) static int check_align(size_t align)
{
    if (align & (align - 1)) /* must be a power of two */
        return EINVAL;
    if (align < sizeof (void *)) /* must be a multiple of sizeof (void *) */
        return EINVAL;
    return 0;
}