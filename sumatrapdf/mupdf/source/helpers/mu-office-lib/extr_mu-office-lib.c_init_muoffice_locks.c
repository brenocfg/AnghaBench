#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; TYPE_2__* user; } ;
typedef  TYPE_1__ fz_locks_context ;
struct TYPE_7__ {TYPE_1__ locks; int /*<<< orphan*/ * mutexes; } ;
typedef  TYPE_2__ MuOfficeLib ;

/* Variables and functions */
 int FZ_LOCK_MAX ; 
 int /*<<< orphan*/  fin_muoffice_locks (TYPE_2__*) ; 
 int mu_create_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  muoffice_lock ; 
 int /*<<< orphan*/  muoffice_unlock ; 

__attribute__((used)) static fz_locks_context *init_muoffice_locks(MuOfficeLib *mu)
{
	int i;
	int failed = 0;

	for (i = 0; i < FZ_LOCK_MAX+1; i++)
		failed |= mu_create_mutex(&mu->mutexes[i]);

	if (failed)
	{
		fin_muoffice_locks(mu);
		return NULL;
	}

	mu->locks.user = mu;
	mu->locks.lock = muoffice_lock;
	mu->locks.unlock = muoffice_unlock;

	return &mu->locks;
}