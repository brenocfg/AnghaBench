#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  lock; TYPE_4__* kstat; } ;
struct TYPE_9__ {TYPE_3__ io_history; } ;
struct TYPE_10__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_2__ spa_t ;
typedef  TYPE_3__ spa_history_kstat_t ;
struct TYPE_12__ {int /*<<< orphan*/  ks_update; TYPE_2__* ks_private; int /*<<< orphan*/ * ks_lock; } ;
typedef  TYPE_4__ kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  KSTAT_TYPE_IO ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 char* kmem_asprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 TYPE_4__* kstat_create (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstat_install (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_io_history_update ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 

__attribute__((used)) static void
spa_io_history_init(spa_t *spa)
{
	spa_history_kstat_t *shk = &spa->spa_stats.io_history;
	char *name;
	kstat_t *ksp;

	mutex_init(&shk->lock, NULL, MUTEX_DEFAULT, NULL);

	name = kmem_asprintf("zfs/%s", spa_name(spa));

	ksp = kstat_create(name, 0, "io", "disk", KSTAT_TYPE_IO, 1, 0);
	shk->kstat = ksp;

	if (ksp) {
		ksp->ks_lock = &shk->lock;
		ksp->ks_private = spa;
		ksp->ks_update = spa_io_history_update;
		kstat_install(ksp);
	}
	kmem_strfree(name);
}