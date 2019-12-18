#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sa_lock; } ;
typedef  TYPE_1__ sa_handle_t ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 TYPE_1__* MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int sa_lookup_impl (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int
sa_bulk_lookup_locked(sa_handle_t *hdl, sa_bulk_attr_t *attrs, int count)
{
	ASSERT(hdl);
	ASSERT(MUTEX_HELD(&hdl->sa_lock));
	return (sa_lookup_impl(hdl, attrs, count));
}