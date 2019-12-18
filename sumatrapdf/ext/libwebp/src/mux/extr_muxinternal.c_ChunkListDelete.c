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
typedef  int /*<<< orphan*/  WebPChunk ;

/* Variables and functions */
 int /*<<< orphan*/ * ChunkDelete (int /*<<< orphan*/ *) ; 

void ChunkListDelete(WebPChunk** const chunk_list) {
  while (*chunk_list != NULL) {
    *chunk_list = ChunkDelete(*chunk_list);
  }
}