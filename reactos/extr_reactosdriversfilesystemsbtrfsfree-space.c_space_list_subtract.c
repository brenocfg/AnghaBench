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
struct TYPE_4__ {int /*<<< orphan*/  space_size; void* space_changed; void* changed; int /*<<< orphan*/  space; int /*<<< orphan*/  deleting; } ;
typedef  TYPE_1__ chunk ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  space_list_subtract2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

void space_list_subtract(chunk* c, BOOL deleting, UINT64 address, UINT64 length, LIST_ENTRY* rollback) {
    LIST_ENTRY* list;

    list = deleting ? &c->deleting : &c->space;

    c->changed = TRUE;
    c->space_changed = TRUE;

    space_list_subtract2(list, deleting ? NULL : &c->space_size, address, length, c, rollback);
}