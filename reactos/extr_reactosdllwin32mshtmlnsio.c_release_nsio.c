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
 int /*<<< orphan*/ * net_util ; 
 int /*<<< orphan*/  nsIIOService_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsINetUtil_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nsio ; 

void release_nsio(void)
{
    if(net_util) {
        nsINetUtil_Release(net_util);
        net_util = NULL;
    }

    if(nsio) {
        nsIIOService_Release(nsio);
        nsio = NULL;
    }
}