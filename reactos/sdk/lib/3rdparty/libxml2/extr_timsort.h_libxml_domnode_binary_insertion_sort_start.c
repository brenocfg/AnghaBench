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
typedef  int /*<<< orphan*/  SORT_TYPE ;

/* Variables and functions */
 size_t BINARY_INSERTION_FIND (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ SORT_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BINARY_INSERTION_SORT_START(SORT_TYPE *dst, const size_t start, const size_t size) {
  size_t i;

  for (i = start; i < size; i++) {
    size_t j;
    SORT_TYPE x;
    size_t location;

    /* If this entry is already correct, just move along */
    if (SORT_CMP(dst[i - 1], dst[i]) <= 0) {
      continue;
    }

    /* Else we need to find the right place, shift everything over, and squeeze in */
    x = dst[i];
    location = BINARY_INSERTION_FIND(dst, x, i);

    for (j = i - 1; j >= location; j--) {
      dst[j + 1] = dst[j];

      if (j == 0) { /* check edge case because j is unsigned */
        break;
      }
    }

    dst[location] = x;
  }
}