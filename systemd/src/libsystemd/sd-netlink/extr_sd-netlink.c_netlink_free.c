#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* floating; } ;
typedef  TYPE_1__ sd_netlink_slot ;
struct TYPE_10__ {unsigned int rqueue_size; unsigned int rqueue_partial_size; int /*<<< orphan*/  fd; int /*<<< orphan*/  nlmsg_type_to_genl_family; int /*<<< orphan*/  genl_family_to_nlmsg_type; int /*<<< orphan*/  broadcast_group_refs; int /*<<< orphan*/  event; int /*<<< orphan*/  time_event_source; int /*<<< orphan*/  io_event_source; int /*<<< orphan*/  reply_callbacks_prioq; int /*<<< orphan*/  reply_callbacks; TYPE_1__* slots; int /*<<< orphan*/ * rbuffer; int /*<<< orphan*/ * rqueue_partial; int /*<<< orphan*/ * rqueue; } ;
typedef  TYPE_2__ sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  netlink_slot_disconnect (TYPE_1__*,int) ; 
 int /*<<< orphan*/  prioq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_message_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_netlink *netlink_free(sd_netlink *rtnl) {
        sd_netlink_slot *s;
        unsigned i;

        assert(rtnl);

        for (i = 0; i < rtnl->rqueue_size; i++)
                sd_netlink_message_unref(rtnl->rqueue[i]);
        free(rtnl->rqueue);

        for (i = 0; i < rtnl->rqueue_partial_size; i++)
                sd_netlink_message_unref(rtnl->rqueue_partial[i]);
        free(rtnl->rqueue_partial);

        free(rtnl->rbuffer);

        while ((s = rtnl->slots)) {
                assert(s->floating);
                netlink_slot_disconnect(s, true);
        }
        hashmap_free(rtnl->reply_callbacks);
        prioq_free(rtnl->reply_callbacks_prioq);

        sd_event_source_unref(rtnl->io_event_source);
        sd_event_source_unref(rtnl->time_event_source);
        sd_event_unref(rtnl->event);

        hashmap_free(rtnl->broadcast_group_refs);

        hashmap_free(rtnl->genl_family_to_nlmsg_type);
        hashmap_free(rtnl->nlmsg_type_to_genl_family);

        safe_close(rtnl->fd);
        return mfree(rtnl);
}