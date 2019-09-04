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
struct TYPE_4__ {int /*<<< orphan*/  chm_index; int /*<<< orphan*/  chm_file; } ;
struct TYPE_5__ {TYPE_1__ merge; int /*<<< orphan*/  local; int /*<<< orphan*/  name; struct TYPE_5__* child; struct TYPE_5__* next; } ;
typedef  TYPE_2__ ContentItem ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_content_item(ContentItem *item)
{
    ContentItem *next;

    while(item) {
        next = item->next;

        free_content_item(item->child);

        heap_free(item->name);
        heap_free(item->local);
        heap_free(item->merge.chm_file);
        heap_free(item->merge.chm_index);

        item = next;
    }
}