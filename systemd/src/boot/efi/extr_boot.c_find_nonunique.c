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
typedef  size_t UINTN ;
struct TYPE_3__ {void* non_unique; int /*<<< orphan*/  title_show; } ;
typedef  TYPE_1__ ConfigEntry ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ StrCmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TRUE ; 

__attribute__((used)) static BOOLEAN find_nonunique(ConfigEntry **entries, UINTN entry_count) {
        BOOLEAN non_unique = FALSE;
        UINTN i, k;

        for (i = 0; i < entry_count; i++)
                entries[i]->non_unique = FALSE;

        for (i = 0; i < entry_count; i++)
                for (k = 0; k < entry_count; k++) {
                        if (i == k)
                                continue;
                        if (StrCmp(entries[i]->title_show, entries[k]->title_show) != 0)
                                continue;

                        non_unique = entries[i]->non_unique = entries[k]->non_unique = TRUE;
                }

        return non_unique;
}