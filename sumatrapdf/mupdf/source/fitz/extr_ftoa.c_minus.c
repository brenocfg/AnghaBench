#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ f; scalar_t__ member_0; scalar_t__ e; scalar_t__ member_1; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static diy_fp_t
minus(diy_fp_t x, diy_fp_t y)
{
	diy_fp_t result = {x.f - y.f, x.e};
	assert(x.e == y.e && x.f >= y.f);
	return result;
}