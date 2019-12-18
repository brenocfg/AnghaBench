#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* name; scalar_t__ section; TYPE_1__* tunnel; } ;
struct TYPE_6__ {int /*<<< orphan*/  sessions_by_section; } ;
typedef  TYPE_2__ L2tpSession ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  ordered_hashmap_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void l2tp_session_free(L2tpSession *s) {
        if (!s)
                return;

        if (s->tunnel && s->section)
                ordered_hashmap_remove(s->tunnel->sessions_by_section, s);

        network_config_section_free(s->section);

        free(s->name);

        free(s);
}