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
struct TYPE_3__ {int /*<<< orphan*/  e; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * powers_ten ; 
 int /*<<< orphan*/ * powers_ten_e ; 

__attribute__((used)) static diy_fp_t
cached_power(int i)
{
	diy_fp_t result;

	assert (i >= -37 && i <= 46);
	result.f = powers_ten[i + 37];
	result.e = powers_ten_e[i + 37];
	return result;
}