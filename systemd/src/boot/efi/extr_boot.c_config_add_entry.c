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
typedef  int UINTN ;
struct TYPE_3__ {int entry_count; int /*<<< orphan*/ ** entries; } ;
typedef  int /*<<< orphan*/  ConfigEntry ;
typedef  TYPE_1__ Config ;

/* Variables and functions */
 int /*<<< orphan*/ ** AllocatePool (int) ; 
 int /*<<< orphan*/ ** ReallocatePool (int /*<<< orphan*/ **,int,int) ; 

__attribute__((used)) static VOID config_add_entry(Config *config, ConfigEntry *entry) {
        if ((config->entry_count & 15) == 0) {
                UINTN i;

                i = config->entry_count + 16;
                if (config->entry_count == 0)
                        config->entries = AllocatePool(sizeof(VOID *) * i);
                else
                        config->entries = ReallocatePool(config->entries,
                                                         sizeof(VOID *) * config->entry_count, sizeof(VOID *) * i);
        }
        config->entries[config->entry_count++] = entry;
}