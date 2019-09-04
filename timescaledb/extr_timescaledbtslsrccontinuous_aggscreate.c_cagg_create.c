#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_32__ {int is_default; int /*<<< orphan*/  parsed; } ;
typedef  TYPE_1__ WithClauseResult ;
struct TYPE_33__ {TYPE_3__* view; int /*<<< orphan*/ * options; int /*<<< orphan*/  aliases; } ;
typedef  TYPE_2__ ViewStmt ;
struct TYPE_37__ {int htid; int /*<<< orphan*/  htoid; int /*<<< orphan*/  bucket_width; int /*<<< orphan*/  htpartcoltype; } ;
struct TYPE_36__ {int /*<<< orphan*/  matcollist; } ;
struct TYPE_35__ {int /*<<< orphan*/  rtable; struct TYPE_35__* groupClause; } ;
struct TYPE_34__ {int /*<<< orphan*/  relname; int /*<<< orphan*/  schemaname; } ;
typedef  TYPE_3__ RangeVar ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_4__ Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_5__ MatTableColumnInfo ;
typedef  int /*<<< orphan*/  Interval ;
typedef  int /*<<< orphan*/  FinalizeQueryInfo ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;
typedef  TYPE_6__ CAggTimebucketInfo ;

/* Variables and functions */
 size_t ContinuousViewOptionCreateGroupIndex ; 
 size_t ContinuousViewOptionRefreshInterval ; 
 int /*<<< orphan*/ * DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HYPERTABLE ; 
 char* INTERNAL_SCHEMA_NAME ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  PRINT_MATINTERNAL_NAME (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetCreationNamespace (TYPE_3__*) ; 
 int /*<<< orphan*/  cagg_add_trigger_hypertable (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* copyObject (TYPE_4__*) ; 
 int /*<<< orphan*/  create_cagg_catlog_entry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_view_for_query (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_4__* finalizequery_get_select_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finalizequery_init (int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  fixup_userview_query_tlist (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_max_interval_per_job (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_refresh_lag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * list_nth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* makeRangeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mattablecolumninfo_addinternal (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mattablecolumninfo_create_materialization_table (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_6__*,int,int /*<<< orphan*/ *) ; 
 TYPE_4__* mattablecolumninfo_get_partial_select_query (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mattablecolumninfo_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_table_next_seq_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_continuous_agg_job_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cagg_create(ViewStmt *stmt, Query *panquery, CAggTimebucketInfo *origquery_ht,
			WithClauseResult *with_clause_options)
{
	ObjectAddress mataddress;
	char relnamebuf[NAMEDATALEN];
	MatTableColumnInfo mattblinfo;
	FinalizeQueryInfo finalqinfo;
	CatalogSecurityContext sec_ctx;
	bool is_create_mattbl_index;

	Query *final_selquery;
	Query *partial_selquery;	/* query to populate the mattable*/
	Query *orig_userview_query; /* copy of the original user query for dummy view */
	RangeTblEntry *usertbl_rte;
	Oid nspid;
	RangeVar *part_rel = NULL, *mat_rel = NULL, *dum_rel = NULL;
	int32 materialize_hypertable_id;
	int32 job_id;
	char trigarg[NAMEDATALEN];
	int ret;
	Interval *refresh_interval =
		DatumGetIntervalP(with_clause_options[ContinuousViewOptionRefreshInterval].parsed);
	int64 refresh_lag = get_refresh_lag(origquery_ht->htpartcoltype,
										origquery_ht->bucket_width,
										with_clause_options);
	int64 max_interval_per_job = get_max_interval_per_job(origquery_ht->htpartcoltype,
														  with_clause_options,
														  origquery_ht->bucket_width);

	/* assign the column_name aliases in CREATE VIEW to the query. No other modifications to
	 * panquery */
	fixup_userview_query_tlist(panquery, stmt->aliases);
	mattablecolumninfo_init(&mattblinfo, NIL, NIL, copyObject(panquery->groupClause));
	finalizequery_init(&finalqinfo, panquery, &mattblinfo);

	/* invalidate all options on the stmt before using it
	 * The options are valid only for internal use (ts_continuous)
	 */
	stmt->options = NULL;

	/* Step 0: add any internal columns needed for materialization based
		on the user query's table
	*/
	usertbl_rte = list_nth(panquery->rtable, 0);
	mattablecolumninfo_addinternal(&mattblinfo, usertbl_rte, origquery_ht->htid);

	/* Step 1: create the materialization table */
	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	materialize_hypertable_id = ts_catalog_table_next_seq_id(ts_catalog_get(), HYPERTABLE);
	ts_catalog_restore_user(&sec_ctx);
	PRINT_MATINTERNAL_NAME(relnamebuf, "_materialized_hypertable_%d", materialize_hypertable_id);
	mat_rel = makeRangeVar(pstrdup(INTERNAL_SCHEMA_NAME), pstrdup(relnamebuf), -1);
	is_create_mattbl_index = with_clause_options[ContinuousViewOptionCreateGroupIndex].is_default;
	mattablecolumninfo_create_materialization_table(&mattblinfo,
													materialize_hypertable_id,
													mat_rel,
													origquery_ht,
													is_create_mattbl_index,
													&mataddress);
	/* Step 2: create view with select finalize from materialization
	 * table
	 */
	final_selquery =
		finalizequery_get_select_query(&finalqinfo, mattblinfo.matcollist, &mataddress);
	create_view_for_query(final_selquery, stmt->view);

	/* Step 3: create the internal view with select partialize(..)
	 */
	partial_selquery = mattablecolumninfo_get_partial_select_query(&mattblinfo, panquery);

	PRINT_MATINTERNAL_NAME(relnamebuf, "_partial_view_%d", materialize_hypertable_id);
	part_rel = makeRangeVar(pstrdup(INTERNAL_SCHEMA_NAME), pstrdup(relnamebuf), -1);
	create_view_for_query(partial_selquery, part_rel);

	/* Additional miscellaneous steps */
	/* create a dummy view to store the user supplied view query. This is to get PG
	 * to display the view correctly without having to replicate the PG source code for make_viewdef
	 */
	orig_userview_query = copyObject(panquery);
	PRINT_MATINTERNAL_NAME(relnamebuf, "_direct_view_%d", materialize_hypertable_id);
	dum_rel = makeRangeVar(pstrdup(INTERNAL_SCHEMA_NAME), pstrdup(relnamebuf), -1);
	create_view_for_query(orig_userview_query, dum_rel);

	/* register the BGW job to process continuous aggs*/
	job_id =
		ts_continuous_agg_job_add(origquery_ht->htid, origquery_ht->bucket_width, refresh_interval);

	/* Step 4 add catalog table entry for the objects we just created */
	nspid = RangeVarGetCreationNamespace(stmt->view);
	create_cagg_catlog_entry(materialize_hypertable_id,
							 origquery_ht->htid,
							 get_namespace_name(nspid), /*schema name for user view */
							 stmt->view->relname,
							 part_rel->schemaname,
							 part_rel->relname,
							 origquery_ht->bucket_width,
							 refresh_lag,
							 max_interval_per_job,
							 job_id,
							 dum_rel->schemaname,
							 dum_rel->relname);

	/* Step 5 create trigger on raw hypertable -specified in the user view query*/
	ret = snprintf(trigarg, NAMEDATALEN, "%d", origquery_ht->htid);
	if (ret < 0 || ret >= NAMEDATALEN)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("bad argument to continuous aggregate trigger")));
	cagg_add_trigger_hypertable(origquery_ht->htoid, trigarg);

	return;
}