#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * chunk; } ;
struct TYPE_9__ {int /*<<< orphan*/  associated_table_prefix; int /*<<< orphan*/  associated_schema_name; } ;
struct TYPE_10__ {TYPE_1__ fd; int /*<<< orphan*/  space; int /*<<< orphan*/  chunk_cache; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_2__ Hypertable ;
typedef  TYPE_3__ ChunkStoreEntry ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* hypertable_chunk_store_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_chunk_create (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_chunk_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* ts_subspace_store_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline Chunk *
hypertable_get_chunk(Hypertable *h, Point *point, bool create_if_not_exists)
{
	Chunk *chunk;
	ChunkStoreEntry *cse = ts_subspace_store_get(h->chunk_cache, point);
	if (cse != NULL)
	{
		Assert(NULL != cse->chunk);
		return cse->chunk;
	}

	/*
	 * ts_chunk_find() must execute on a per-tuple memory context since it
	 * allocates a lot of transient data. We don't want this allocated on
	 * the cache's memory context.
	 */
	chunk = ts_chunk_find(h->space, point);

	if (NULL == chunk)
	{
		if (!create_if_not_exists)
			return NULL;

		chunk = ts_chunk_create(h,
								point,
								NameStr(h->fd.associated_schema_name),
								NameStr(h->fd.associated_table_prefix));
	}

	Assert(chunk != NULL);

	/* Also add the chunk to the hypertable's chunk store */
	cse = hypertable_chunk_store_add(h, chunk);
	return chunk;
}