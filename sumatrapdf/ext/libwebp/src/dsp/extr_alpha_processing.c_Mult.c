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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int HALF ; 
 int MFIX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint32_t Mult(uint8_t x, uint32_t mult) {
  const uint32_t v = (x * mult + HALF) >> MFIX;
  assert(v <= 255);  // <- 24bit precision is enough to ensure that.
  return v;
}