#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FormData_hypertable_compression ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 char* compression_column_segment_max_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_attnum (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static AttrNumber
get_segment_meta_max_attr_number(FormData_hypertable_compression *compression_info,
								 Oid compressed_relid)
{
	char *meta_col_name = compression_column_segment_max_name(compression_info);

	if (meta_col_name == NULL)
		elog(ERROR, "could not find meta column");

	return get_attnum(compressed_relid, meta_col_name);
}