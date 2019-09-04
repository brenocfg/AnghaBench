#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_8__ {int /*<<< orphan*/  options; int /*<<< orphan*/  attlist; scalar_t__ is_program; int /*<<< orphan*/ * filename; int /*<<< orphan*/ * relation; int /*<<< orphan*/  query; int /*<<< orphan*/  is_from; } ;
struct TYPE_7__ {char const* p_sourcetext; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_2__ CopyStmt ;
typedef  int /*<<< orphan*/  CopyState ;
typedef  int /*<<< orphan*/  CopyChunkState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BeginCopyFrom (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EndCopyFrom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/ * copy_chunk_state_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_security_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  free_parsestate (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_openrv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* make_parsestate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_copy_from ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  timescaledb_CopyFrom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * timescaledb_CopyGetAttnums (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
timescaledb_DoCopy(const CopyStmt *stmt, const char *queryString, uint64 *processed, Hypertable *ht)
{
	CopyChunkState *ccstate;
	CopyState cstate;
	bool pipe = (stmt->filename == NULL);
	Relation rel;
	List *range_table = NIL;
	List *attnums = NIL;

	/* Disallow COPY to/from file or program except to superusers. */
	if (!pipe && !superuser())
	{
		if (stmt->is_program)
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to COPY to or from an external program"),
					 errhint("Anyone can COPY to stdout or from stdin. "
							 "psql's \\copy command also works for anyone.")));
		else
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to COPY to or from a file"),
					 errhint("Anyone can COPY to stdout or from stdin. "
							 "psql's \\copy command also works for anyone.")));
	}

	if (!stmt->is_from || NULL == stmt->relation)
		elog(ERROR, "timescale DoCopy should only be called for COPY FROM");

	Assert(!stmt->query);

	/*
	 * We never actually write to the main table, but we need RowExclusiveLock
	 * to ensure no one else is
	 */
	rel = heap_openrv(stmt->relation, RowExclusiveLock);

	attnums = timescaledb_CopyGetAttnums(RelationGetDescr(rel), rel, stmt->attlist);

	copy_security_check(rel, attnums);

#if PG96
	cstate = BeginCopyFrom(rel, stmt->filename, stmt->is_program, stmt->attlist, stmt->options);
#else
	{
		ParseState *pstate = make_parsestate(NULL);

		pstate->p_sourcetext = queryString;
		cstate = BeginCopyFrom(pstate,
							   rel,
							   stmt->filename,
							   stmt->is_program,
							   NULL,
							   stmt->attlist,
							   stmt->options);
		free_parsestate(pstate);
	}
#endif
	ccstate = copy_chunk_state_create(ht, rel, next_copy_from, cstate);

	*processed = timescaledb_CopyFrom(ccstate, range_table, ht);
	EndCopyFrom(cstate);

	heap_close(rel, NoLock);
}