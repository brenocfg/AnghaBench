#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* os_phys; int /*<<< orphan*/  os_spa; } ;
typedef  TYPE_2__ objset_t ;
typedef  int boolean_t ;
struct TYPE_5__ {size_t os_type; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DMU_USERUSED_DNODE (TYPE_2__*) ; 
 scalar_t__ SPA_VERSION_USERSPACE ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** used_cbs ; 

boolean_t
dmu_objset_userused_enabled(objset_t *os)
{
	return (spa_version(os->os_spa) >= SPA_VERSION_USERSPACE &&
	    used_cbs[os->os_phys->os_type] != NULL &&
	    DMU_USERUSED_DNODE(os) != NULL);
}