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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_message_hash_ops ; 
 int sd_bus_message_get_expect_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_message_ref (int /*<<< orphan*/ *) ; 
 int set_ensure_allocated (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_add_message(Set **set, sd_bus_message *message) {
        int r;

        assert(set);

        if (!message)
                return 0;

        r = sd_bus_message_get_expect_reply(message);
        if (r <= 0)
                return r;

        r = set_ensure_allocated(set, &bus_message_hash_ops);
        if (r < 0)
                return r;

        r = set_put(*set, message);
        if (r < 0)
                return r;

        sd_bus_message_ref(message);
        return 1;
}