#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gt_opr; int /*<<< orphan*/  lt_opr; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_9__ {int /*<<< orphan*/  attname; scalar_t__ orderby_asc; scalar_t__ orderby_nullsfirst; } ;
struct TYPE_8__ {int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attcollation; int /*<<< orphan*/  attnum; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  TYPE_3__ ColumnCompressionInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 scalar_t__ COMPRESSIONCOL_IS_SEGMENT_BY (TYPE_3__ const*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheAttName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TYPECACHE_GT_OPR ; 
 int TYPECACHE_LT_OPR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
compress_chunk_populate_sort_info_for_column(Oid table, const ColumnCompressionInfo *column,
											 AttrNumber *att_nums, Oid *sort_operator,
											 Oid *collation, bool *nulls_first)
{
	HeapTuple tp;
	Form_pg_attribute att_tup;
	TypeCacheEntry *tentry;

	tp = SearchSysCacheAttName(table, NameStr(column->attname));
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "table %d does not have column \"%s\"", table, NameStr(column->attname));

	att_tup = (Form_pg_attribute) GETSTRUCT(tp);
	// TODO other valdation checks?

	*att_nums = att_tup->attnum;
	*collation = att_tup->attcollation;
	*nulls_first = (!(COMPRESSIONCOL_IS_SEGMENT_BY(column))) && column->orderby_nullsfirst;

	tentry = lookup_type_cache(att_tup->atttypid, TYPECACHE_LT_OPR | TYPECACHE_GT_OPR);

	if (COMPRESSIONCOL_IS_SEGMENT_BY(column) || column->orderby_asc)
		*sort_operator = tentry->lt_opr;
	else
		*sort_operator = tentry->gt_opr;

	if (!OidIsValid(*sort_operator))
		elog(ERROR,
			 "no valid sort operator for column \"%s\" of type \"%s\"",
			 NameStr(column->attname),
			 format_type_be(att_tup->atttypid));

	ReleaseSysCache(tp);
}