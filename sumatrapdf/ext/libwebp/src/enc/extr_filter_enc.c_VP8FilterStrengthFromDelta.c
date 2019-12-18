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
 int MAX_DELTA_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int** kLevelsFromDelta ; 

int VP8FilterStrengthFromDelta(int sharpness, int delta) {
  const int pos = (delta < MAX_DELTA_SIZE) ? delta : MAX_DELTA_SIZE - 1;
  assert(sharpness >= 0 && sharpness <= 7);
  return kLevelsFromDelta[sharpness][pos];
}