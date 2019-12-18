#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iovec_wrapper {size_t count; TYPE_1__* iovec; } ;
struct TYPE_2__ {scalar_t__ iov_len; } ;

/* Variables and functions */

size_t iovw_size(struct iovec_wrapper *iovw) {
        size_t n = 0, i;

        for (i = 0; i < iovw->count; i++)
                n += iovw->iovec[i].iov_len;

        return n;
}