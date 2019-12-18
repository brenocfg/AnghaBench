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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int8_numeric ; 
 int /*<<< orphan*/  numeric_add ; 
 int /*<<< orphan*/  numeric_div ; 
 int /*<<< orphan*/  numeric_mul ; 
 int /*<<< orphan*/  numeric_sub ; 

__attribute__((used)) static Datum
interpolate_numeric(int64 x_i, int64 x0_i, int64 x1_i, Datum y0, Datum y1)
{
	Datum x0 = DirectFunctionCall1(int8_numeric, Int64GetDatum(x0_i));
	Datum x1 = DirectFunctionCall1(int8_numeric, Int64GetDatum(x1_i));
	Datum x = DirectFunctionCall1(int8_numeric, Int64GetDatum(x_i));

	Datum x1_sub_x = DirectFunctionCall2(numeric_sub, x1, x);
	Datum x_sub_x0 = DirectFunctionCall2(numeric_sub, x, x0);
	Datum y0_mul_x1_sub_x = DirectFunctionCall2(numeric_mul, y0, x1_sub_x);
	Datum y1_mul_x_sub_x0 = DirectFunctionCall2(numeric_mul, y1, x_sub_x0);

	Datum numerator = DirectFunctionCall2(numeric_add, y0_mul_x1_sub_x, y1_mul_x_sub_x0);
	Datum denominator = DirectFunctionCall2(numeric_sub, x1, x0);

	return DirectFunctionCall2(numeric_div, numerator, denominator);
}