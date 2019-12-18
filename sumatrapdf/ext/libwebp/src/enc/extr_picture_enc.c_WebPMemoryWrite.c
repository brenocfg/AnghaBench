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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  unsigned long long uint64_t ;
struct TYPE_4__ {scalar_t__ custom_ptr; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_5__ {size_t size; unsigned long long max_size; int /*<<< orphan*/  const* mem; } ;
typedef  TYPE_2__ WebPMemoryWriter ;

/* Variables and functions */
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/  const*) ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int WebPMemoryWrite(const uint8_t* data, size_t data_size,
                    const WebPPicture* picture) {
  WebPMemoryWriter* const w = (WebPMemoryWriter*)picture->custom_ptr;
  uint64_t next_size;
  if (w == NULL) {
    return 1;
  }
  next_size = (uint64_t)w->size + data_size;
  if (next_size > w->max_size) {
    uint8_t* new_mem;
    uint64_t next_max_size = 2ULL * w->max_size;
    if (next_max_size < next_size) next_max_size = next_size;
    if (next_max_size < 8192ULL) next_max_size = 8192ULL;
    new_mem = (uint8_t*)WebPSafeMalloc(next_max_size, 1);
    if (new_mem == NULL) {
      return 0;
    }
    if (w->size > 0) {
      memcpy(new_mem, w->mem, w->size);
    }
    WebPSafeFree(w->mem);
    w->mem = new_mem;
    // down-cast is ok, thanks to WebPSafeMalloc
    w->max_size = (size_t)next_max_size;
  }
  if (data_size > 0) {
    memcpy(w->mem + w->size, data, data_size);
    w->size += data_size;
  }
  return 1;
}