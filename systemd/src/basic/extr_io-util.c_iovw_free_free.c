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
struct iovec_wrapper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iovw_free_contents (struct iovec_wrapper*,int) ; 
 struct iovec_wrapper* mfree (struct iovec_wrapper*) ; 

struct iovec_wrapper *iovw_free_free(struct iovec_wrapper *iovw) {
        iovw_free_contents(iovw, true);

        return mfree(iovw);
}