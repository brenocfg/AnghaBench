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
struct TYPE_3__ {int /*<<< orphan*/  mls_list; int /*<<< orphan*/  mls_lock; } ;
typedef  TYPE_1__ multilist_sublist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int list_is_empty (int /*<<< orphan*/ *) ; 

int
multilist_sublist_is_empty(multilist_sublist_t *mls)
{
	ASSERT(MUTEX_HELD(&mls->mls_lock));
	return (list_is_empty(&mls->mls_list));
}