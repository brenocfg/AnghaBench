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
 int /*<<< orphan*/  BINARY_INSERTION_SORT_START (int /*<<< orphan*/ *,int,size_t const) ; 

void BINARY_INSERTION_SORT(SORT_TYPE *dst, const size_t size) {
  /* don't bother sorting an array of size <= 1 */
  if (size <= 1) {
    return;
  }

  BINARY_INSERTION_SORT_START(dst, 1, size);
}