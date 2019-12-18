#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/  family; } ;
struct TYPE_16__ {TYPE_1__ ip; } ;
struct TYPE_15__ {int /*<<< orphan*/  seen_family; void* seen_at; void* used_at; } ;
struct TYPE_14__ {TYPE_9__ ip_port; int /*<<< orphan*/  timestamp; } ;
struct TYPE_13__ {void* ret_timestamp; int /*<<< orphan*/  ret_ip_port; int /*<<< orphan*/  timestamp; TYPE_9__ ip_port; } ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  TYPE_2__ IPPTsPng ;
typedef  TYPE_3__ IPPTs ;
typedef  TYPE_4__ Client_entry ;
typedef  int /*<<< orphan*/  Assoc ;

/* Variables and functions */
 TYPE_2__* entry_assoc (TYPE_4__*,TYPE_9__*) ; 
 int /*<<< orphan*/  entry_heard_store (TYPE_4__*,TYPE_3__ const*) ; 
 void* unix_time () ; 

__attribute__((used)) static void candidates_update_assoc(const Assoc *assoc, Client_entry *entry, uint8_t used, const IPPTs *ippts_send,
                                    const IP_Port *ipp_recv)
{
    if (!assoc || !entry || !ippts_send)
        return;

    IPPTsPng *ipptsp = entry_assoc(entry, &ippts_send->ip_port);

    if (!ipptsp)
        return;

    if (used)
        entry->used_at = unix_time();

    /* do NOT do anything related to wanted, that's handled outside,
     * just update the assoc (in the most sensible way)
     */
    if (ipp_recv) {
        ipptsp->ip_port = ippts_send->ip_port;
        ipptsp->timestamp = ippts_send->timestamp;
        ipptsp->ret_ip_port = *ipp_recv;
        ipptsp->ret_timestamp = unix_time();

        entry->seen_at = unix_time();
        entry->seen_family = ippts_send->ip_port.ip.family;

        return;
    }

    entry_heard_store(entry, ippts_send);
}