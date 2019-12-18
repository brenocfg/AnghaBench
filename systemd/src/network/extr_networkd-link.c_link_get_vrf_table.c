#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
struct TYPE_6__ {TYPE_1__* network; } ;
struct TYPE_5__ {scalar_t__ vrf; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 TYPE_4__* VRF (scalar_t__) ; 

uint32_t link_get_vrf_table(Link *link) {
        return link->network->vrf ? VRF(link->network->vrf)->table : RT_TABLE_MAIN;
}