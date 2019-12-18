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
 int LOOPBACK_IFINDEX ; 

int dns_synthesize_ifindex(int ifindex) {

        /* When the caller asked for resolving on a specific
         * interface, we synthesize the answer for that
         * interface. However, if nothing specific was claimed and we
         * only return localhost RRs, we synthesize the answer for
         * localhost. */

        if (ifindex > 0)
                return ifindex;

        return LOOPBACK_IFINDEX;
}