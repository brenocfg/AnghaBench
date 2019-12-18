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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t UINTN ;
struct TYPE_3__ {size_t entry_count; int /*<<< orphan*/ * entry_oneshot; int /*<<< orphan*/ * options_edit; int /*<<< orphan*/ * entry_default_pattern; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ Config ;

/* Variables and functions */
 int /*<<< orphan*/  FreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_entry_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID config_free(Config *config) {
        UINTN i;

        for (i = 0; i < config->entry_count; i++)
                config_entry_free(config->entries[i]);
        FreePool(config->entries);
        FreePool(config->entry_default_pattern);
        FreePool(config->options_edit);
        FreePool(config->entry_oneshot);
}