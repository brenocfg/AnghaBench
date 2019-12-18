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
struct TYPE_5__ {int /*<<< orphan*/  table_id; TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Path ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * compress_chunk_dml_path_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Path *
compress_chunk_dml_generate_paths(Path *subpath, Chunk *chunk)
{
	Assert(chunk->fd.compressed_chunk_id > 0);
	return compress_chunk_dml_path_create(subpath, chunk->table_id);
}