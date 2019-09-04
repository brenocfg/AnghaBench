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
struct TYPE_4__ {scalar_t__ magic; } ;
typedef  TYPE_1__ node_t ;
typedef  int /*<<< orphan*/  heap_t ;

/* Variables and functions */
 TYPE_1__* heap_remove_any (int /*<<< orphan*/ *) ; 

__attribute__((used)) static node_t *
node_remove_any(heap_t *heap) {
	node_t *node = heap_remove_any(heap);
	node->magic = 0;
	return node;
}