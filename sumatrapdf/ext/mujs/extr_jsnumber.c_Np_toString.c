#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_7__ {double number; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ js_Object ;
struct TYPE_9__ {char* s; } ;
typedef  TYPE_3__ js_Buffer ;

/* Variables and functions */
 scalar_t__ JS_CNUMBER ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 char* jsV_numbertostring (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_3__**,char) ; 
 int /*<<< orphan*/  js_rangeerror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* js_toobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 
 double pow (int,int) ; 

__attribute__((used)) static void Np_toString(js_State *J)
{
	char buf[100];
	js_Object *self = js_toobject(J, 0);
	int radix = js_isundefined(J, 1) ? 10 : js_tointeger(J, 1);
	if (self->type != JS_CNUMBER)
		js_typeerror(J, "not a number");
	if (radix == 10) {
		js_pushstring(J, jsV_numbertostring(J, buf, self->u.number));
		return;
	}
	if (radix < 2 || radix > 36)
		js_rangeerror(J, "invalid radix");

	/* lame number to string conversion for any radix from 2 to 36 */
	{
		static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
		double number = self->u.number;
		int sign = self->u.number < 0;
		js_Buffer *sb = NULL;
		uint64_t u, limit = ((uint64_t)1<<52);

		int ndigits, exp, point;

		if (number == 0) { js_pushstring(J, "0"); return; }
		if (isnan(number)) { js_pushstring(J, "NaN"); return; }
		if (isinf(number)) { js_pushstring(J, sign ? "-Infinity" : "Infinity"); return; }

		if (sign)
			number = -number;

		/* fit as many digits as we want in an int */
		exp = 0;
		while (number * pow(radix, exp) > limit)
			--exp;
		while (number * pow(radix, exp+1) < limit)
			++exp;
		u = number * pow(radix, exp) + 0.5;

		/* trim trailing zeros */
		while (u > 0 && (u % radix) == 0) {
			u /= radix;
			--exp;
		}

		/* serialize digits */
		ndigits = 0;
		while (u > 0) {
			buf[ndigits++] = digits[u % radix];
			u /= radix;
		}
		point = ndigits - exp;

		if (js_try(J)) {
			js_free(J, sb);
			js_throw(J);
		}

		if (sign)
			js_putc(J, &sb, '-');

		if (point <= 0) {
			js_putc(J, &sb, '0');
			js_putc(J, &sb, '.');
			while (point++ < 0)
				js_putc(J, &sb, '0');
			while (ndigits-- > 0)
				js_putc(J, &sb, buf[ndigits]);
		} else {
			while (ndigits-- > 0) {
				js_putc(J, &sb, buf[ndigits]);
				if (--point == 0 && ndigits > 0)
					js_putc(J, &sb, '.');
			}
			while (point-- > 0)
				js_putc(J, &sb, '0');
		}

		js_putc(J, &sb, 0);
		js_pushstring(J, sb->s);

		js_endtry(J);
		js_free(J, sb);
	}
}