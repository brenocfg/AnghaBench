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
struct iovec_wrapper {scalar_t__ count; int /*<<< orphan*/ * iovec; int /*<<< orphan*/  size_bytes; } ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  GREEDY_REALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IOVEC_MAKE (void*,size_t) ; 
 scalar_t__ IOV_MAX ; 
 int log_oom () ; 

int iovw_put(struct iovec_wrapper *iovw, void *data, size_t len) {
        if (iovw->count >= IOV_MAX)
                return -E2BIG;

        if (!GREEDY_REALLOC(iovw->iovec, iovw->size_bytes, iovw->count + 1))
                return log_oom();

        iovw->iovec[iovw->count++] = IOVEC_MAKE(data, len);
        return 0;
}