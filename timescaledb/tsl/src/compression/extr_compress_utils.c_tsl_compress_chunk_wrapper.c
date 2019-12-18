#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ compressed_chunk_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  hypertable_relid; TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INVALID_CHUNK_ID ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  compress_chunk_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 TYPE_2__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool
tsl_compress_chunk_wrapper(Oid chunk_relid, bool if_not_compressed)
{
	Chunk *srcchunk = ts_chunk_get_by_relid(chunk_relid, 0, true);
	if (srcchunk->fd.compressed_chunk_id != INVALID_CHUNK_ID)
	{
		ereport((if_not_compressed ? NOTICE : ERROR),
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("chunk \"%s\" is already compressed", get_rel_name(chunk_relid))));
		return false;
	}

	compress_chunk_impl(srcchunk->hypertable_relid, chunk_relid);
	return true;
}