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
struct reply_callback {scalar_t__ timeout_usec; } ;

/* Variables and functions */
 int CMP (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int timeout_compare(const void *a, const void *b) {
        const struct reply_callback *x = a, *y = b;

        if (x->timeout_usec != 0 && y->timeout_usec == 0)
                return -1;

        if (x->timeout_usec == 0 && y->timeout_usec != 0)
                return 1;

        return CMP(x->timeout_usec, y->timeout_usec);
}