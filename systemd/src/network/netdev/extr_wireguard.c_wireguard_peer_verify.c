#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* section; int /*<<< orphan*/  preshared_key_file; int /*<<< orphan*/  preshared_key; int /*<<< orphan*/  public_key; int /*<<< orphan*/  wireguard; } ;
typedef  TYPE_1__ WireguardPeer ;
struct TYPE_5__ {int /*<<< orphan*/  line; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  NetDev ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * NETDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int) ; 
 scalar_t__ eqzero (int /*<<< orphan*/ ) ; 
 int log_netdev_error_errno (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ section_is_invalid (TYPE_3__*) ; 
 int wireguard_read_key_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wireguard_peer_verify(WireguardPeer *peer) {
        NetDev *netdev = NETDEV(peer->wireguard);
        int r;

        if (section_is_invalid(peer->section))
                return -EINVAL;

        if (eqzero(peer->public_key))
                return log_netdev_error_errno(netdev, SYNTHETIC_ERRNO(EINVAL),
                                              "%s: WireGuardPeer section without PublicKey= configured. "
                                              "Ignoring [WireGuardPeer] section from line %u.",
                                              peer->section->filename, peer->section->line);

        r = wireguard_read_key_file(peer->preshared_key_file, peer->preshared_key);
        if (r < 0)
                return log_netdev_error_errno(netdev, r,
                                              "%s: Failed to read preshared key from '%s'. "
                                              "Ignoring [WireGuardPeer] section from line %u.",
                                              peer->section->filename, peer->preshared_key_file,
                                              peer->section->line);

        return 0;
}