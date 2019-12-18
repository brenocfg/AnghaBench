#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tag_; } ;
typedef  TYPE_1__ WebPChunk ;

/* Variables and functions */
 int /*<<< orphan*/  NIL_TAG ; 
 int /*<<< orphan*/  assert (TYPE_1__* const) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

void ChunkInit(WebPChunk* const chunk) {
  assert(chunk);
  memset(chunk, 0, sizeof(*chunk));
  chunk->tag_ = NIL_TAG;
}