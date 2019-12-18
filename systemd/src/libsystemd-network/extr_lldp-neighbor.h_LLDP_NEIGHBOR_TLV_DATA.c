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
typedef  void uint8_t ;
struct TYPE_4__ {int rindex; } ;
typedef  TYPE_1__ sd_lldp_neighbor ;

/* Variables and functions */
 scalar_t__ LLDP_NEIGHBOR_RAW (TYPE_1__ const*) ; 

__attribute__((used)) static inline void* LLDP_NEIGHBOR_TLV_DATA(const sd_lldp_neighbor *n) {
        return ((uint8_t*) LLDP_NEIGHBOR_RAW(n)) + n->rindex + 2;
}