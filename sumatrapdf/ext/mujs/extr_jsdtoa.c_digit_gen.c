#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int f; int e; } ;
typedef  TYPE_1__ diy_fp_t ;

/* Variables and functions */
 int TEN2 ; 

__attribute__((used)) static void digit_gen(diy_fp_t Mp, diy_fp_t delta, char* buffer, int* len, int* K)
{
	uint32_t div, p1;
	uint64_t p2;
	int d,kappa;
	diy_fp_t one;
	one.f = ((uint64_t) 1) << -Mp.e; one.e = Mp.e;
	p1 = Mp.f >> -one.e;
	p2 = Mp.f & (one.f - 1);
	*len = 0; kappa = 3; div = TEN2;
	while (kappa > 0) {
		d = p1 / div;
		if (d || *len) buffer[(*len)++] = '0' + d;
		p1 %= div; kappa--; div /= 10;
		if ((((uint64_t)p1)<<-one.e)+p2 <= delta.f) {
			*K += kappa; return;
		}
	}
	do {
		p2 *= 10;
		d = p2 >> -one.e;
		if (d || *len) buffer[(*len)++] = '0' + d;
		p2 &= one.f - 1; kappa--; delta.f *= 10;
	} while (p2 > delta.f);
	*K += kappa;
}