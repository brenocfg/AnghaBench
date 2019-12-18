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
struct TYPE_3__ {scalar_t__ default_entry; int /*<<< orphan*/ * entries; } ;
typedef  int /*<<< orphan*/  BootEntry ;
typedef  TYPE_1__ BootConfig ;

/* Variables and functions */

__attribute__((used)) static inline BootEntry* boot_config_default_entry(BootConfig *config) {
        if (config->default_entry < 0)
                return NULL;

        return config->entries + config->default_entry;
}