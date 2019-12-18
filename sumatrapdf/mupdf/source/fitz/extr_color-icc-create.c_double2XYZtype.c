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
typedef  int /*<<< orphan*/  icS15Fixed16Number ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static icS15Fixed16Number
double2XYZtype(fz_context *ctx, float number_in)
{
	short s;
	unsigned short m;

	if (number_in < 0)
		number_in = 0;
	s = (short)number_in;
	m = (unsigned short)((number_in - s) * 65536);
	return (icS15Fixed16Number) ((s << 16) | m);
}