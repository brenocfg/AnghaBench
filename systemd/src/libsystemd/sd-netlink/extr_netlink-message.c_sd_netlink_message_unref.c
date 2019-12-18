#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ n_ref; unsigned int n_containers; struct TYPE_7__* next; TYPE_1__* containers; struct TYPE_7__* hdr; } ;
typedef  TYPE_2__ sd_netlink_message ;
struct TYPE_6__ {TYPE_2__* attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

sd_netlink_message *sd_netlink_message_unref(sd_netlink_message *m) {
        while (m && --m->n_ref == 0) {
                unsigned i;

                free(m->hdr);

                for (i = 0; i <= m->n_containers; i++)
                        free(m->containers[i].attributes);

                sd_netlink_message *t = m;
                m = m->next;
                free(t);
        }

        return NULL;
}