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
 int /*<<< orphan*/  REVERSE_ELEMENTS (int /*<<< orphan*/ *,size_t const,size_t) ; 
 scalar_t__ SORT_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t COUNT_RUN(SORT_TYPE *dst, const size_t start, const size_t size) {
  size_t curr;

  if (size - start == 1) {
    return 1;
  }

  if (start >= size - 2) {
    if (SORT_CMP(dst[size - 2], dst[size - 1]) > 0) {
      SORT_SWAP(dst[size - 2], dst[size - 1]);
    }

    return 2;
  }

  curr = start + 2;

  if (SORT_CMP(dst[start], dst[start + 1]) <= 0) {
    /* increasing run */
    while (1) {
      if (curr == size - 1) {
        break;
      }

      if (SORT_CMP(dst[curr - 1], dst[curr]) > 0) {
        break;
      }

      curr++;
    }

    return curr - start;
  } else {
    /* decreasing run */
    while (1) {
      if (curr == size - 1) {
        break;
      }

      if (SORT_CMP(dst[curr - 1], dst[curr]) <= 0) {
        break;
      }

      curr++;
    }

    /* reverse in-place */
    REVERSE_ELEMENTS(dst, start, curr - 1);
    return curr - start;
  }
}