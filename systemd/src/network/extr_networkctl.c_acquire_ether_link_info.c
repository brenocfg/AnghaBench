#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int has_ethtool_link_info; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autonegotiation; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ LinkInfo ;

/* Variables and functions */
 scalar_t__ ethtool_get_link_info (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acquire_ether_link_info(int *fd, LinkInfo *link) {
        if (ethtool_get_link_info(fd, link->name,
                                  &link->autonegotiation,
                                  &link->speed,
                                  &link->duplex,
                                  &link->port) >= 0)
                link->has_ethtool_link_info = true;
}