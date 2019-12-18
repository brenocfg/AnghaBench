#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rows; int startup_cost; int total_cost; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 int DECOMPRESS_CHUNK_BATCH_SIZE ; 
 int DECOMPRESS_CHUNK_CPU_TUPLE_COST ; 

__attribute__((used)) static void
cost_decompress_chunk(Path *path, Path *compressed_path)
{
	/* startup_cost is cost before fetching first tuple */
	if (compressed_path->rows > 0)
		path->startup_cost = compressed_path->total_cost / compressed_path->rows;

	/* total_cost is cost for fetching all tuples */
	path->total_cost = compressed_path->total_cost + path->rows * DECOMPRESS_CHUNK_CPU_TUPLE_COST;
	path->rows = compressed_path->rows * DECOMPRESS_CHUNK_BATCH_SIZE;
}