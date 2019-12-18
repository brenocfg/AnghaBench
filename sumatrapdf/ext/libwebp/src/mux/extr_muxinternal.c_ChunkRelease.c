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
struct TYPE_5__ {struct TYPE_5__* next_; int /*<<< orphan*/  data_; scalar_t__ owner_; } ;
typedef  TYPE_1__ WebPChunk ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkInit (TYPE_1__* const) ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ *) ; 

WebPChunk* ChunkRelease(WebPChunk* const chunk) {
  WebPChunk* next;
  if (chunk == NULL) return NULL;
  if (chunk->owner_) {
    WebPDataClear(&chunk->data_);
  }
  next = chunk->next_;
  ChunkInit(chunk);
  return next;
}