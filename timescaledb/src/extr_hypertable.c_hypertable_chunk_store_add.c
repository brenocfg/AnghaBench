#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cube; } ;
struct TYPE_11__ {int /*<<< orphan*/  chunk; int /*<<< orphan*/  mcxt; } ;
struct TYPE_10__ {int /*<<< orphan*/  chunk_cache; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ Hypertable ;
typedef  TYPE_2__ ChunkStoreEntry ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_store_entry_free ; 
 TYPE_2__* palloc (int) ; 
 int /*<<< orphan*/  ts_chunk_copy (TYPE_3__*) ; 
 int /*<<< orphan*/  ts_subspace_store_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_subspace_store_mcxt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ChunkStoreEntry *
hypertable_chunk_store_add(Hypertable *h, Chunk *chunk)
{
	ChunkStoreEntry *cse;
	MemoryContext old_mcxt, chunk_mcxt;

	chunk_mcxt = AllocSetContextCreate(ts_subspace_store_mcxt(h->chunk_cache),
									   "chunk cache entry memory context",
									   ALLOCSET_SMALL_SIZES);

	/* Add the chunk to the subspace store */
	old_mcxt = MemoryContextSwitchTo(chunk_mcxt);
	cse = palloc(sizeof(ChunkStoreEntry));
	cse->mcxt = chunk_mcxt;
	cse->chunk = ts_chunk_copy(chunk);
	ts_subspace_store_add(h->chunk_cache, chunk->cube, cse, chunk_store_entry_free);
	MemoryContextSwitchTo(old_mcxt);

	return cse;
}