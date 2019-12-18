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
typedef  enum bus_state { ____Placeholder_bus_state } bus_state ;

/* Variables and functions */
 int BUS_CLOSING ; 
 int BUS_UNSET ; 

__attribute__((used)) static inline bool BUS_IS_OPEN(enum bus_state state) {
        return state > BUS_UNSET && state < BUS_CLOSING;
}