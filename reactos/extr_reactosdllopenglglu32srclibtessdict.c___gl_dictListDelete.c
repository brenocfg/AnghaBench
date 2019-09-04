#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* next; TYPE_1__* prev; } ;
struct TYPE_7__ {TYPE_1__* prev; } ;
struct TYPE_6__ {TYPE_2__* next; } ;
typedef  TYPE_3__ DictNode ;
typedef  int /*<<< orphan*/  Dict ;

/* Variables and functions */
 int /*<<< orphan*/  memFree (TYPE_3__*) ; 

void dictDelete( Dict *dict, DictNode *node ) /*ARGSUSED*/
{
  node->next->prev = node->prev;
  node->prev->next = node->next;
  memFree( node );
}