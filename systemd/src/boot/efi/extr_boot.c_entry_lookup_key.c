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
typedef  int UINTN ;
struct TYPE_5__ {int entry_count; TYPE_1__** entries; } ;
struct TYPE_4__ {char key; } ;
typedef  TYPE_2__ Config ;
typedef  char CHAR16 ;

/* Variables and functions */

__attribute__((used)) static UINTN entry_lookup_key(Config *config, UINTN start, CHAR16 key) {
        UINTN i;

        if (key == 0)
                return -1;

        /* select entry by number key */
        if (key >= '1' && key <= '9') {
                i = key - '0';
                if (i > config->entry_count)
                        i = config->entry_count;
                return i-1;
        }

        /* find matching key in config entries */
        for (i = start; i < config->entry_count; i++)
                if (config->entries[i]->key == key)
                        return i;

        for (i = 0; i < start; i++)
                if (config->entries[i]->key == key)
                        return i;

        return -1;
}