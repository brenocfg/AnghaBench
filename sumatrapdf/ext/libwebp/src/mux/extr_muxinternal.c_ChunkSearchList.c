#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {struct TYPE_6__* next_; } ;
typedef  TYPE_1__ WebPChunk ;

/* Variables and functions */
 TYPE_1__* ChunkSearchNextInList (TYPE_1__*,scalar_t__) ; 

WebPChunk* ChunkSearchList(WebPChunk* first, uint32_t nth, uint32_t tag) {
  uint32_t iter = nth;
  first = ChunkSearchNextInList(first, tag);
  if (first == NULL) return NULL;

  while (--iter != 0) {
    WebPChunk* next_chunk = ChunkSearchNextInList(first->next_, tag);
    if (next_chunk == NULL) break;
    first = next_chunk;
  }
  return ((nth > 0) && (iter > 0)) ? NULL : first;
}