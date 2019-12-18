#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ section; TYPE_1__* network; } ;
struct TYPE_5__ {int /*<<< orphan*/  qdiscs_by_section; } ;
typedef  TYPE_2__ QDiscs ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  ordered_hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 

void qdisc_free(QDiscs *qdisc) {
        if (!qdisc)
                return;

        if (qdisc->network && qdisc->section)
                ordered_hashmap_remove(qdisc->network->qdiscs_by_section, qdisc->section);

        network_config_section_free(qdisc->section);

        free(qdisc);
}