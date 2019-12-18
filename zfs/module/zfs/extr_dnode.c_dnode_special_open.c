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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;
struct TYPE_4__ {int /*<<< orphan*/  dnh_zrlock; } ;
typedef  TYPE_1__ dnode_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DNODE_VERIFY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dnode_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zrl_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zrl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zrl_tryenter (int /*<<< orphan*/ *) ; 

void
dnode_special_open(objset_t *os, dnode_phys_t *dnp, uint64_t object,
    dnode_handle_t *dnh)
{
	dnode_t *dn;

	zrl_init(&dnh->dnh_zrlock);
	zrl_tryenter(&dnh->dnh_zrlock);

	dn = dnode_create(os, dnp, NULL, object, dnh);
	DNODE_VERIFY(dn);

	zrl_exit(&dnh->dnh_zrlock);
}