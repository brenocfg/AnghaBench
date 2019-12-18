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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  redaction_list_t ;
struct TYPE_3__ {char const* dbcra_bmark; char const* dbcra_snap; void* dbcra_tag; int /*<<< orphan*/ * dbcra_snaps; int /*<<< orphan*/  dbcra_numsnaps; int /*<<< orphan*/ ** dbcra_rl; } ;
typedef  TYPE_1__ dsl_bookmark_create_redacted_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int /*<<< orphan*/  dsl_bookmark_create_redacted_check ; 
 int /*<<< orphan*/  dsl_bookmark_create_redacted_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
dsl_bookmark_create_redacted(const char *bookmark, const char *snapshot,
    uint64_t numsnaps, uint64_t *snapguids, void *tag, redaction_list_t **rl)
{
	dsl_bookmark_create_redacted_arg_t dbcra;

	dbcra.dbcra_bmark = bookmark;
	dbcra.dbcra_snap = snapshot;
	dbcra.dbcra_rl = rl;
	dbcra.dbcra_numsnaps = numsnaps;
	dbcra.dbcra_snaps = snapguids;
	dbcra.dbcra_tag = tag;

	return (dsl_sync_task(bookmark, dsl_bookmark_create_redacted_check,
	    dsl_bookmark_create_redacted_sync, &dbcra, 5,
	    ZFS_SPACE_CHECK_NORMAL));
}