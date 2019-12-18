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
struct TYPE_10__ {int /*<<< orphan*/  preshared_key; struct TYPE_10__* preshared_key_file; struct TYPE_10__* endpoint_port; struct TYPE_10__* endpoint_host; struct TYPE_10__* ipmasks; scalar_t__ section; TYPE_1__* wireguard; } ;
typedef  TYPE_2__ WireguardPeer ;
typedef  TYPE_2__ WireguardIPmask ;
struct TYPE_9__ {int /*<<< orphan*/  peers_by_section; int /*<<< orphan*/  peers_with_failed_endpoint; int /*<<< orphan*/  peers_with_unresolved_endpoint; TYPE_2__* peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  WG_KEY_LEN ; 
 int /*<<< orphan*/  explicit_bzero_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipmasks ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  peers ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void wireguard_peer_free(WireguardPeer *peer) {
        WireguardIPmask *mask;

        if (!peer)
                return;

        if (peer->wireguard) {
                LIST_REMOVE(peers, peer->wireguard->peers, peer);

                set_remove(peer->wireguard->peers_with_unresolved_endpoint, peer);
                set_remove(peer->wireguard->peers_with_failed_endpoint, peer);

                if (peer->section)
                        hashmap_remove(peer->wireguard->peers_by_section, peer->section);
        }

        network_config_section_free(peer->section);

        while ((mask = peer->ipmasks)) {
                LIST_REMOVE(ipmasks, peer->ipmasks, mask);
                free(mask);
        }

        free(peer->endpoint_host);
        free(peer->endpoint_port);
        free(peer->preshared_key_file);
        explicit_bzero_safe(peer->preshared_key, WG_KEY_LEN);

        free(peer);
}