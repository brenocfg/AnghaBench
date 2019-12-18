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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {scalar_t__ bucket_width; int /*<<< orphan*/  htpartcol_interval_len; void* htpartcoltype; int /*<<< orphan*/  htpartcolno; void* htoid; int /*<<< orphan*/  htid; } ;
typedef  void* Oid ;
typedef  TYPE_1__ CAggTimebucketInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */

__attribute__((used)) static void
caggtimebucketinfo_init(CAggTimebucketInfo *src, int32 hypertable_id, Oid hypertable_oid,
						AttrNumber hypertable_partition_colno, Oid hypertable_partition_coltype,
						int64 hypertable_partition_col_interval)
{
	src->htid = hypertable_id;
	src->htoid = hypertable_oid;
	src->htpartcolno = hypertable_partition_colno;
	src->htpartcoltype = hypertable_partition_coltype;
	src->htpartcol_interval_len = hypertable_partition_col_interval;
	src->bucket_width = 0; /*invalid value */
}