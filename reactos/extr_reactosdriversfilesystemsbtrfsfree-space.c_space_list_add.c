#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  deleting; void* space_changed; void* changed; } ;
typedef  TYPE_1__ chunk ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* TRUE ; 
 int /*<<< orphan*/  space_list_add2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

void space_list_add(chunk* c, UINT64 address, UINT64 length, LIST_ENTRY* rollback) {
    TRACE("(%p, %llx, %llx, %p)\n", c, address, length, rollback);

    c->changed = TRUE;
    c->space_changed = TRUE;

    space_list_add2(&c->deleting, NULL, address, length, c, rollback);
}