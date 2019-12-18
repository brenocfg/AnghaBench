#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* content; } ;
struct TYPE_4__ {size_t n_entries; TYPE_3__* entries; } ;
typedef  TYPE_1__ PStoreList ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void pstore_entries_reset(PStoreList *list) {
        for (size_t i = 0; i < list->n_entries; i++)
                free(list->entries[i].content);
        free(list->entries);
        list->n_entries = 0;
}