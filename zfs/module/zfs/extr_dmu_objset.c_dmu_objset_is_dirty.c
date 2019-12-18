#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * os_dirty_dnodes; } ;
typedef  TYPE_1__ objset_t ;
typedef  int boolean_t ;

/* Variables and functions */
 size_t TXG_MASK ; 
 int /*<<< orphan*/  multilist_is_empty (int /*<<< orphan*/ ) ; 

boolean_t
dmu_objset_is_dirty(objset_t *os, uint64_t txg)
{
	return (!multilist_is_empty(os->os_dirty_dnodes[txg & TXG_MASK]));
}