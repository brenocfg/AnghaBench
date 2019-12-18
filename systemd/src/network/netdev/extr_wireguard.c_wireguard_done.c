#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  peers_with_failed_endpoint; int /*<<< orphan*/  peers_with_unresolved_endpoint; int /*<<< orphan*/  peers_by_section; int /*<<< orphan*/  private_key_file; int /*<<< orphan*/  private_key; int /*<<< orphan*/  resolve_retry_event_source; } ;
typedef  TYPE_1__ Wireguard ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  WG_KEY_LEN ; 
 TYPE_1__* WIREGUARD (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  explicit_bzero_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireguard_peer_free ; 

__attribute__((used)) static void wireguard_done(NetDev *netdev) {
        Wireguard *w;

        assert(netdev);
        w = WIREGUARD(netdev);
        assert(w);

        sd_event_source_unref(w->resolve_retry_event_source);

        explicit_bzero_safe(w->private_key, WG_KEY_LEN);
        free(w->private_key_file);

        hashmap_free_with_destructor(w->peers_by_section, wireguard_peer_free);
        set_free(w->peers_with_unresolved_endpoint);
        set_free(w->peers_with_failed_endpoint);
}