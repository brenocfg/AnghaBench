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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {unsigned int f; unsigned int e; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ strtof_fp_t ;

/* Variables and functions */
 unsigned int leading_zeros (int /*<<< orphan*/ ) ; 

__attribute__((used)) static strtof_fp_t
uint32_to_diy (uint32_t x)
{
	strtof_fp_t result = {x, 0};
	unsigned shift = leading_zeros(x);

	result.f <<= shift;
	result.e -= shift;
	return result;
}