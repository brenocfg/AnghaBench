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
typedef  enum bus_match_node_type { ____Placeholder_bus_match_node_type } bus_match_node_type ;

/* Variables and functions */
 int BUS_MATCH_ARG ; 
 int BUS_MATCH_ARG_HAS ; 
 int BUS_MATCH_ARG_HAS_LAST ; 
 int BUS_MATCH_ARG_LAST ; 
 int BUS_MATCH_MESSAGE_TYPE ; 
 int BUS_MATCH_PATH ; 

__attribute__((used)) static bool BUS_MATCH_CAN_HASH(enum bus_match_node_type t) {
        return (t >= BUS_MATCH_MESSAGE_TYPE && t <= BUS_MATCH_PATH) ||
                (t >= BUS_MATCH_ARG && t <= BUS_MATCH_ARG_LAST) ||
                (t >= BUS_MATCH_ARG_HAS && t <= BUS_MATCH_ARG_HAS_LAST);
}