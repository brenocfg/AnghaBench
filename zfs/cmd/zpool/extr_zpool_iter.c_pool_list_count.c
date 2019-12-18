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
struct TYPE_3__ {int /*<<< orphan*/  zl_avl; } ;
typedef  TYPE_1__ zpool_list_t ;

/* Variables and functions */
 int uu_avl_numnodes (int /*<<< orphan*/ ) ; 

int
pool_list_count(zpool_list_t *zlp)
{
	return (uu_avl_numnodes(zlp->zl_avl));
}