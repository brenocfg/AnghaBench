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
struct TYPE_3__ {int /*<<< orphan*/ * mutexes; } ;
typedef  TYPE_1__ MuOfficeLib ;

/* Variables and functions */
 int FZ_LOCK_MAX ; 
 int /*<<< orphan*/  mu_destroy_mutex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fin_muoffice_locks(MuOfficeLib *mu)
{
	int i;

	for (i = 0; i < FZ_LOCK_MAX+1; i++)
		mu_destroy_mutex(&mu->mutexes[i]);
}