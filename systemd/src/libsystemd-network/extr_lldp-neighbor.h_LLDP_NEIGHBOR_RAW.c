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
typedef  void uint8_t ;
typedef  int /*<<< orphan*/  sd_lldp_neighbor ;

/* Variables and functions */
 int ALIGN (int) ; 

__attribute__((used)) static inline void *LLDP_NEIGHBOR_RAW(const sd_lldp_neighbor *n) {
        return (uint8_t*) n + ALIGN(sizeof(sd_lldp_neighbor));
}