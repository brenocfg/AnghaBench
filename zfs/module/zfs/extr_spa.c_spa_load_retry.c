#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_10__ {scalar_t__ ub_txg; } ;
struct TYPE_11__ {int spa_mode; scalar_t__ spa_load_max_txg; TYPE_1__ spa_uberblock; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  spa_load_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_IMPORT_EXISTING ; 
 int /*<<< orphan*/  spa_activate (TYPE_2__*,int) ; 
 int /*<<< orphan*/  spa_async_suspend (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_deactivate (TYPE_2__*) ; 
 int spa_load (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_unload (TYPE_2__*) ; 

__attribute__((used)) static int
spa_load_retry(spa_t *spa, spa_load_state_t state)
{
	int mode = spa->spa_mode;

	spa_unload(spa);
	spa_deactivate(spa);

	spa->spa_load_max_txg = spa->spa_uberblock.ub_txg - 1;

	spa_activate(spa, mode);
	spa_async_suspend(spa);

	spa_load_note(spa, "spa_load_retry: rewind, max txg: %llu",
	    (u_longlong_t)spa->spa_load_max_txg);

	return (spa_load(spa, state, SPA_IMPORT_EXISTING));
}