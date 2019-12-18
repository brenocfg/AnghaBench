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
typedef  size_t UINTN ;
struct TYPE_5__ {size_t entry_count; TYPE_1__** entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  int INTN ;
typedef  TYPE_2__ Config ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 scalar_t__ StrCmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static INTN config_entry_find(Config *config, CHAR16 *id) {
        UINTN i;

        for (i = 0; i < config->entry_count; i++)
                if (StrCmp(config->entries[i]->id, id) == 0)
                        return (INTN) i;

        return -1;
}