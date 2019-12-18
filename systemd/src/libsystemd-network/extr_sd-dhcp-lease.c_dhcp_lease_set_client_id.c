#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t client_id_len; void* client_id; } ;
typedef  TYPE_1__ sd_dhcp_lease ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* memdup (void const*,size_t) ; 
 void* mfree (void*) ; 

int dhcp_lease_set_client_id(sd_dhcp_lease *lease, const void *client_id, size_t client_id_len) {
        assert_return(lease, -EINVAL);
        assert_return(client_id || client_id_len <= 0, -EINVAL);

        if (client_id_len <= 0)
                lease->client_id = mfree(lease->client_id);
        else {
                void *p;

                p = memdup(client_id, client_id_len);
                if (!p)
                        return -ENOMEM;

                free(lease->client_id);
                lease->client_id = p;
                lease->client_id_len = client_id_len;
        }

        return 0;
}