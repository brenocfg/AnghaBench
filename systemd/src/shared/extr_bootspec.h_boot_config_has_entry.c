#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t n_entries; TYPE_1__* entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ BootConfig ;

/* Variables and functions */
 scalar_t__ streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline bool boot_config_has_entry(BootConfig *config, const char *id) {
        size_t j;

        for (j = 0; j < config->n_entries; j++)
                if (streq(config->entries[j].id, id))
                        return true;

        return false;
}