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
struct TYPE_4__ {int /*<<< orphan*/  zv_hash; int /*<<< orphan*/  zv_hlink; } ;
typedef  TYPE_1__ zvol_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVOL_HT_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_state_list ; 
 int /*<<< orphan*/  zvol_state_lock ; 

void
zvol_insert(zvol_state_t *zv)
{
	ASSERT(RW_WRITE_HELD(&zvol_state_lock));
	list_insert_head(&zvol_state_list, zv);
	hlist_add_head(&zv->zv_hlink, ZVOL_HT_HEAD(zv->zv_hash));
}