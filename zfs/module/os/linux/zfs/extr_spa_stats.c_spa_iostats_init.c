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
struct TYPE_9__ {TYPE_3__ iostats; } ;
struct TYPE_10__ {TYPE_1__ spa_stats; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  spa_iostats_t ;
typedef  TYPE_3__ spa_history_kstat_t ;
struct TYPE_12__ {int /*<<< orphan*/  ks_data; int /*<<< orphan*/  ks_update; TYPE_2__* ks_private; int /*<<< orphan*/ * ks_lock; } ;
typedef  TYPE_4__ kstat_t ;
typedef  int /*<<< orphan*/  kstat_named_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  KSTAT_FLAG_VIRTUAL ; 
 int /*<<< orphan*/  KSTAT_TYPE_NAMED ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  kmem_alloc (int,int /*<<< orphan*/ ) ; 
 char* kmem_asprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 TYPE_4__* kstat_create (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstat_install (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_iostats_template ; 
 int /*<<< orphan*/  spa_iostats_update ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 

__attribute__((used)) static void
spa_iostats_init(spa_t *spa)
{
	spa_history_kstat_t *shk = &spa->spa_stats.iostats;

	mutex_init(&shk->lock, NULL, MUTEX_DEFAULT, NULL);

	char *name = kmem_asprintf("zfs/%s", spa_name(spa));
	kstat_t *ksp = kstat_create(name, 0, "iostats", "misc",
	    KSTAT_TYPE_NAMED, sizeof (spa_iostats_t) / sizeof (kstat_named_t),
	    KSTAT_FLAG_VIRTUAL);

	shk->kstat = ksp;
	if (ksp) {
		int size = sizeof (spa_iostats_t);
		ksp->ks_lock = &shk->lock;
		ksp->ks_private = spa;
		ksp->ks_update = spa_iostats_update;
		ksp->ks_data = kmem_alloc(size, KM_SLEEP);
		memcpy(ksp->ks_data, &spa_iostats_template, size);
		kstat_install(ksp);
	}

	kmem_strfree(name);
}