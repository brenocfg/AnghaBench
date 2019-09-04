#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  prev; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  ME_DIType ;

/* Variables and functions */
 TYPE_1__* heap_alloc_zero (int) ; 

ME_DisplayItem *ME_MakeDI(ME_DIType type)
{
  ME_DisplayItem *item = heap_alloc_zero(sizeof(*item));

  item->type = type;
  item->prev = item->next = NULL;
  return item;
}