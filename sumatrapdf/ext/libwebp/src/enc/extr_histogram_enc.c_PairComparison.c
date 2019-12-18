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

/* Variables and functions */

__attribute__((used)) static int PairComparison(const void* idx1, const void* idx2) {
  // To be used with bsearch: <0 when *idx1<*idx2, >0 if >, 0 when ==.
  return (*(int*) idx1 - *(int*) idx2);
}