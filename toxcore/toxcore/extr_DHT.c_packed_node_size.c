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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int PACKED_NODE_SIZE_IP4 ; 
 int PACKED_NODE_SIZE_IP6 ; 
 scalar_t__ TCP_INET ; 
 scalar_t__ TCP_INET6 ; 

int packed_node_size(uint8_t ip_family)
{
    if (ip_family == AF_INET) {
        return PACKED_NODE_SIZE_IP4;
    } else if (ip_family == TCP_INET) {
        return PACKED_NODE_SIZE_IP4;
    } else if (ip_family == AF_INET6) {
        return PACKED_NODE_SIZE_IP6;
    } else if (ip_family == TCP_INET6) {
        return PACKED_NODE_SIZE_IP6;
    } else {
        return -1;
    }
}