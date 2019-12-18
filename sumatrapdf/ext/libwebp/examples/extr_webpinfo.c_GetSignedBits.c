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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetBits (int /*<<< orphan*/  const* const,size_t,int,int*,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static int GetSignedBits(const uint8_t* const data, size_t data_size, size_t nb,
                         int* val, uint64_t* const bit_pos) {
  int sign;
  if (!GetBits(data, data_size, nb, val, bit_pos)) return 0;
  if (!GetBits(data, data_size, 1, &sign, bit_pos)) return 0;
  if (sign) *val = -(*val);
  return 1;
}