#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* data; struct TYPE_6__* next; TYPE_1__* list; } ;
struct TYPE_5__ {scalar_t__ length; TYPE_2__* end; TYPE_2__* begin; } ;
typedef  TYPE_1__ CdioList_t ;
typedef  TYPE_2__ CdioListNode_t ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 

void
_cdio_list_prepend (CdioList_t *p_list, void *p_data)
{
  CdioListNode_t *p_new_node;

  cdio_assert (p_list != NULL);

  p_new_node = calloc (1, sizeof (CdioListNode_t));
  cdio_assert (p_new_node != NULL);

  p_new_node->list = p_list;
  p_new_node->next = p_list->begin;
  p_new_node->data = p_data;

  p_list->begin = p_new_node;
  if (p_list->length == 0)
    p_list->end = p_new_node;

  p_list->length++;
}