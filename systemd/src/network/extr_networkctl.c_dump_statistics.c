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
typedef  int /*<<< orphan*/  Table ;
struct TYPE_3__ {int /*<<< orphan*/  has_stats; int /*<<< orphan*/  has_stats64; } ;
typedef  TYPE_1__ LinkInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_STATS_ONE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_stats ; 
 int /*<<< orphan*/  collisions ; 
 int /*<<< orphan*/  multicast ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_dropped ; 
 int /*<<< orphan*/  rx_errors ; 
 int /*<<< orphan*/  rx_packets ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_dropped ; 
 int /*<<< orphan*/  tx_errors ; 
 int /*<<< orphan*/  tx_packets ; 

__attribute__((used)) static int dump_statistics(Table *table, const LinkInfo *info) {
        int r;

        if (!arg_stats)
                return 0;

        if (!info->has_stats64 && !info->has_stats)
                return 0;

        DUMP_STATS_ONE("Rx Packets", rx_packets);
        DUMP_STATS_ONE("Tx Packets", tx_packets);
        DUMP_STATS_ONE("Rx Bytes", rx_bytes);
        DUMP_STATS_ONE("Tx Bytes", tx_bytes);
        DUMP_STATS_ONE("Rx Errors", rx_errors);
        DUMP_STATS_ONE("Tx Errors", tx_errors);
        DUMP_STATS_ONE("Rx Dropped", rx_dropped);
        DUMP_STATS_ONE("Tx Dropped", tx_dropped);
        DUMP_STATS_ONE("Multicast Packets", multicast);
        DUMP_STATS_ONE("Collisions", collisions);

        return 0;
}