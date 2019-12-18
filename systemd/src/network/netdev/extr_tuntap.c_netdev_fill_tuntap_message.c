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
struct ifreq {scalar_t__ kind; struct ifreq* ifname; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifr_flags; } ;
struct TYPE_4__ {scalar_t__ vnet_hdr; scalar_t__ multi_queue; int /*<<< orphan*/  packet_info; } ;
typedef  TYPE_1__ TunTap ;
typedef  struct ifreq NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_MULTI_QUEUE ; 
 int /*<<< orphan*/  IFF_NO_PI ; 
 int /*<<< orphan*/  IFF_TAP ; 
 int /*<<< orphan*/  IFF_TUN ; 
 int /*<<< orphan*/  IFF_VNET_HDR ; 
 scalar_t__ IFNAMSIZ ; 
 scalar_t__ NETDEV_KIND_TAP ; 
 TYPE_1__* TAP (struct ifreq*) ; 
 TYPE_1__* TUN (struct ifreq*) ; 
 int /*<<< orphan*/  assert (struct ifreq*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,struct ifreq*,scalar_t__) ; 

__attribute__((used)) static int netdev_fill_tuntap_message(NetDev *netdev, struct ifreq *ifr) {
        TunTap *t;

        assert(netdev);
        assert(netdev->ifname);
        assert(ifr);

        if (netdev->kind == NETDEV_KIND_TAP) {
                t = TAP(netdev);
                ifr->ifr_flags |= IFF_TAP;
        } else {
                t = TUN(netdev);
                ifr->ifr_flags |= IFF_TUN;
        }

        if (!t->packet_info)
                ifr->ifr_flags |= IFF_NO_PI;

        if (t->multi_queue)
                ifr->ifr_flags |= IFF_MULTI_QUEUE;

        if (t->vnet_hdr)
                ifr->ifr_flags |= IFF_VNET_HDR;

        strncpy(ifr->ifr_name, netdev->ifname, IFNAMSIZ-1);

        return 0;
}