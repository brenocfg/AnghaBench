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
 int LocalTZA () ; 
 double MakeDate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeDay (int,int,int) ; 
 int /*<<< orphan*/  MakeTime (int,int,int,int) ; 
 double NAN ; 
 int msPerHour ; 
 int msPerMinute ; 
 int /*<<< orphan*/  toint (char const**,int,int*) ; 

__attribute__((used)) static double parseDateTime(const char *s)
{
	int y = 1970, m = 1, d = 1, H = 0, M = 0, S = 0, ms = 0;
	int tza = 0;
	double t;

	/* Parse ISO 8601 formatted date and time: */
	/* YYYY("-"MM("-"DD)?)?("T"HH":"mm(":"ss("."sss)?)?("Z"|[+-]HH(":"mm)?)?)? */

	if (!toint(&s, 4, &y)) return NAN;
	if (*s == '-') {
		s += 1;
		if (!toint(&s, 2, &m)) return NAN;
		if (*s == '-') {
			s += 1;
			if (!toint(&s, 2, &d)) return NAN;
		}
	}

	if (*s == 'T') {
		s += 1;
		if (!toint(&s, 2, &H)) return NAN;
		if (*s != ':') return NAN;
		s += 1;
		if (!toint(&s, 2, &M)) return NAN;
		if (*s == ':') {
			s += 1;
			if (!toint(&s, 2, &S)) return NAN;
			if (*s == '.') {
				s += 1;
				if (!toint(&s, 3, &ms)) return NAN;
			}
		}
		if (*s == 'Z') {
			s += 1;
			tza = 0;
		} else if (*s == '+' || *s == '-') {
			int tzh = 0, tzm = 0;
			int tzs = *s == '+' ? 1 : -1;
			s += 1;
			if (!toint(&s, 2, &tzh)) return NAN;
			if (*s == ':') {
				s += 1;
				if (!toint(&s, 2, &tzm)) return NAN;
			}
			if (tzh > 23 || tzm > 59) return NAN;
			tza = tzs * (tzh * msPerHour + tzm * msPerMinute);
		} else {
			tza = LocalTZA();
		}
	}

	if (*s) return NAN;

	if (m < 1 || m > 12) return NAN;
	if (d < 1 || d > 31) return NAN;
	if (H < 0 || H > 24) return NAN;
	if (M < 0 || M > 59) return NAN;
	if (S < 0 || S > 59) return NAN;
	if (ms < 0 || ms > 999) return NAN;
	if (H == 24 && (M != 0 || S != 0 || ms != 0)) return NAN;

	/* TODO: DaylightSavingTA on local times */
	t = MakeDate(MakeDay(y, m-1, d), MakeTime(H, M, S, ms));
	return t - tza;
}