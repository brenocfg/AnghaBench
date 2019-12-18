#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* compressed_rte; TYPE_1__* ht_rte; } ;
struct TYPE_6__ {int /*<<< orphan*/  relid; } ;
struct TYPE_5__ {int /*<<< orphan*/  relid; } ;
typedef  TYPE_3__ CompressionInfo ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 char* get_attname_compat (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ get_attnum (int /*<<< orphan*/ ,char*) ; 

AttrNumber
get_compressed_attno(CompressionInfo *info, AttrNumber ht_attno)
{
	AttrNumber compressed_attno;
	char *chunk_col = get_attname_compat(info->ht_rte->relid, ht_attno, false);
	compressed_attno = get_attnum(info->compressed_rte->relid, chunk_col);

	if (compressed_attno == InvalidAttrNumber)
		elog(ERROR, "No matching column in compressed chunk found.");

	return compressed_attno;
}