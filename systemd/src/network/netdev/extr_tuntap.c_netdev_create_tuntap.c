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
struct ifreq {int dummy; } ;
typedef  int /*<<< orphan*/  NetDev ;

/* Variables and functions */
 int netdev_fill_tuntap_message (int /*<<< orphan*/ *,struct ifreq*) ; 
 int netdev_tuntap_add (int /*<<< orphan*/ *,struct ifreq*) ; 

__attribute__((used)) static int netdev_create_tuntap(NetDev *netdev) {
        struct ifreq ifr = {};
        int r;

        r = netdev_fill_tuntap_message(netdev, &ifr);
        if (r < 0)
                return r;

        return netdev_tuntap_add(netdev, &ifr);
}