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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  Hyperspace ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  append_chunk ; 
 int /*<<< orphan*/ ** chunk_find_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

Chunk **
ts_chunk_find_all(Hyperspace *hs, List *dimension_vecs, LOCKMODE lockmode, unsigned int *num_chunks)
{
	return chunk_find_all(hs, dimension_vecs, append_chunk, lockmode, num_chunks);
}