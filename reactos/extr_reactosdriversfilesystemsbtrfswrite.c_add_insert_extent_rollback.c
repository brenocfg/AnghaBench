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
struct TYPE_4__ {int /*<<< orphan*/ * ext; int /*<<< orphan*/ * fcb; } ;
typedef  TYPE_1__ rollback_extent ;
typedef  int /*<<< orphan*/  fcb ;
typedef  int /*<<< orphan*/  extent ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ROLLBACK_INSERT_EXTENT ; 
 int /*<<< orphan*/  add_rollback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void add_insert_extent_rollback(LIST_ENTRY* rollback, fcb* fcb, extent* ext) {
    rollback_extent* re;

    re = ExAllocatePoolWithTag(NonPagedPool, sizeof(rollback_extent), ALLOC_TAG);
    if (!re) {
        ERR("out of memory\n");
        return;
    }

    re->fcb = fcb;
    re->ext = ext;

    add_rollback(rollback, ROLLBACK_INSERT_EXTENT, re);
}