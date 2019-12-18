#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dbcra_rl; int /*<<< orphan*/  dbcra_tag; int /*<<< orphan*/  dbcra_snaps; int /*<<< orphan*/  dbcra_numsnaps; int /*<<< orphan*/  dbcra_snap; int /*<<< orphan*/  dbcra_bmark; } ;
typedef  TYPE_1__ dsl_bookmark_create_redacted_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_bookmark_create_sync_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_bookmark_create_redacted_sync(void *arg, dmu_tx_t *tx)
{
	dsl_bookmark_create_redacted_arg_t *dbcra = arg;
	dsl_bookmark_create_sync_impl(dbcra->dbcra_bmark, dbcra->dbcra_snap, tx,
	    dbcra->dbcra_numsnaps, dbcra->dbcra_snaps, dbcra->dbcra_tag,
	    dbcra->dbcra_rl);
}