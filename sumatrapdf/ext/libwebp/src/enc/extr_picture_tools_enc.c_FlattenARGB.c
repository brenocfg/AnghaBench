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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static void FlattenARGB(uint32_t* ptr, uint32_t v, int stride, int size) {
  int x, y;
  for (y = 0; y < size; ++y) {
    for (x = 0; x < size; ++x) ptr[x] = v;
    ptr += stride;
  }
}