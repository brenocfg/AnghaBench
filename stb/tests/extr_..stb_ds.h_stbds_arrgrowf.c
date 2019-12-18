#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stbds_array_header ;
struct TYPE_3__ {size_t capacity; scalar_t__ hash_table; scalar_t__ length; } ;

/* Variables and functions */
 void* STBDS_REALLOC (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  STBDS_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbds_array_grow ; 
 int stbds_arrcap (void*) ; 
 size_t stbds_arrlen (void*) ; 
 TYPE_1__* stbds_header (void*) ; 

void *stbds_arrgrowf(void *a, size_t elemsize, size_t addlen, size_t min_cap)
{
  void *b;
  size_t min_len = stbds_arrlen(a) + addlen;

  // compute the minimum capacity needed
  if (min_len > min_cap)
    min_cap = min_len;

  if (min_cap <= stbds_arrcap(a))
    return a;

  // increase needed capacity to guarantee O(1) amortized
  if (min_cap < 2 * stbds_arrcap(a))
    min_cap = 2 * stbds_arrcap(a);
  else if (min_cap < 4)
    min_cap = 4;

  b = STBDS_REALLOC(NULL, (a) ? stbds_header(a) : 0, elemsize * min_cap + sizeof(stbds_array_header));
  b = (char *) b + sizeof(stbds_array_header);
  if (a == NULL) {
    stbds_header(b)->length = 0;
    stbds_header(b)->hash_table = 0;
  } else {
    STBDS_STATS(++stbds_array_grow);
  }
  stbds_header(b)->capacity = min_cap;
  return b;
}