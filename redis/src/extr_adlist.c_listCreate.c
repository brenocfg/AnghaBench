#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct list {int /*<<< orphan*/ * match; int /*<<< orphan*/ * free; int /*<<< orphan*/ * dup; scalar_t__ len; int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
typedef  struct list list ;

/* Variables and functions */
 struct list* zmalloc (int) ; 

list *listCreate(void)
{
    struct list *list;

    if ((list = zmalloc(sizeof(*list))) == NULL)
        return NULL;
    list->head = list->tail = NULL;
    list->len = 0;
    list->dup = NULL;
    list->free = NULL;
    list->match = NULL;
    return list;
}