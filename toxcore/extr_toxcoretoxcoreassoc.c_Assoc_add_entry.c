#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ hash_t ;
struct TYPE_13__ {scalar_t__ self_hash; int /*<<< orphan*/  self_client_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  const ip_port; } ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  TYPE_1__ IPPTs ;
typedef  int /*<<< orphan*/  Client_entry ;
typedef  TYPE_2__ Assoc ;

/* Variables and functions */
 scalar_t__ candidates_create_new (TYPE_2__*,scalar_t__,int const*,int,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  candidates_search (TYPE_2__*,int const*,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  candidates_update_assoc (TYPE_2__*,int /*<<< orphan*/ *,int,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  client_id_self_update (TYPE_2__*) ; 
 scalar_t__ id_equal (int const*,int /*<<< orphan*/ ) ; 
 scalar_t__ id_hash (TYPE_2__*,int const*) ; 
 int /*<<< orphan*/  ipport_isset (int /*<<< orphan*/  const*) ; 

uint8_t Assoc_add_entry(Assoc *assoc, const uint8_t *id, const IPPTs *ippts_send, const IP_Port *ipp_recv, uint8_t used)
{
    if (!assoc || !id || !ippts_send)
        return 0;

    if (!assoc->self_hash) {
        client_id_self_update(assoc);

        if (!assoc->self_hash)
            return 0;
    }

    if (!ipport_isset(&ippts_send->ip_port))
        return 0;

    if (ipp_recv && !ipport_isset(ipp_recv))
        ipp_recv = NULL;

    hash_t hash = id_hash(assoc, id);

    if (hash == assoc->self_hash)
        if (id_equal(id, assoc->self_client_id))
            return 0;

    /* if it's new:
     * callback, if there's desire, add to clients, else to candidates
     *
     * if it's "old":
     *    if it's client: refresh
     *    if it's candidate:
     *       if !ipp_recv, refresh
     *       if ipp_recv: callback, if there's desire, move to candidates
     */
    Client_entry *cnd_entry;

    if (!candidates_search(assoc, id, hash, &cnd_entry)) {
        if (candidates_create_new(assoc, hash, id, used, ippts_send, ipp_recv))
            return 1;
        else
            return 0;
    } else {
        candidates_update_assoc(assoc, cnd_entry, used, ippts_send, ipp_recv);
        return 2;
    }
}