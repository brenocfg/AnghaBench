#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ client_id; } ;
typedef  TYPE_2__ DHCPLease ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 

__attribute__((used)) static DHCPLease *dhcp_lease_free(DHCPLease *lease) {
        if (!lease)
                return NULL;

        free(lease->client_id.data);
        return mfree(lease);
}