#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  lt_opr; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_17__ {int numcols; TYPE_4__* col_meta; void* coldeflist; } ;
struct TYPE_16__ {scalar_t__ orderby_column_index; int /*<<< orphan*/  attname; } ;
struct TYPE_15__ {int /*<<< orphan*/  atttypid; } ;
struct TYPE_14__ {int /*<<< orphan*/  rd_id; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__ FormData_hypertable_compression ;
typedef  TYPE_5__ CompressColInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPRESSION_COLUMN_METADATA_COUNT_NAME ; 
 int /*<<< orphan*/  COMPRESSION_COLUMN_METADATA_SEQUENCE_NUM_NAME ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_2__*) ; 
 int /*<<< orphan*/  TYPECACHE_LT_OPR ; 
 TYPE_3__* TupleDescAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compression_column_segment_max_name (TYPE_4__*) ; 
 int /*<<< orphan*/  compression_column_segment_min_name (TYPE_4__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_attnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* lappend (void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeColumnDef (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compresscolinfo_add_metadata_columns(CompressColInfo *cc, Relation uncompressed_rel)
{
	/* additional metadata columns.
	 * these are not listed in hypertable_compression catalog table
	 * and so only has a ColDef entry */
	int colno;

	/* count column */
	cc->coldeflist = lappend(cc->coldeflist,

							 /* count of the number of uncompressed rows */
							 makeColumnDef(COMPRESSION_COLUMN_METADATA_COUNT_NAME,
										   INT4OID,
										   -1 /* typemod */,
										   0 /*collation*/));
	/* sequence_num column */
	cc->coldeflist = lappend(cc->coldeflist,

							 /* count of the number of uncompressed rows */
							 makeColumnDef(COMPRESSION_COLUMN_METADATA_SEQUENCE_NUM_NAME,
										   INT4OID,
										   -1 /* typemod */,
										   0 /*collation*/));

	for (colno = 0; colno < cc->numcols; colno++)
	{
		if (cc->col_meta[colno].orderby_column_index > 0)
		{
			FormData_hypertable_compression fd = cc->col_meta[colno];
			AttrNumber col_attno = get_attnum(uncompressed_rel->rd_id, NameStr(fd.attname));
			Form_pg_attribute attr = TupleDescAttr(RelationGetDescr(uncompressed_rel),
												   AttrNumberGetAttrOffset(col_attno));
			TypeCacheEntry *type = lookup_type_cache(attr->atttypid, TYPECACHE_LT_OPR);

			if (!OidIsValid(type->lt_opr))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_FUNCTION),
						 errmsg("invalid order by column type: could not identify an less-than "
								"operator for type %s",
								format_type_be(attr->atttypid))));

			/* segment_meta min and max columns */
			cc->coldeflist =
				lappend(cc->coldeflist,
						makeColumnDef(compression_column_segment_min_name(&cc->col_meta[colno]),
									  attr->atttypid,
									  -1 /* typemod */,
									  0 /*collation*/));
			cc->coldeflist =
				lappend(cc->coldeflist,
						makeColumnDef(compression_column_segment_max_name(&cc->col_meta[colno]),
									  attr->atttypid,
									  -1 /* typemod */,
									  0 /*collation*/));
		}
	}
}