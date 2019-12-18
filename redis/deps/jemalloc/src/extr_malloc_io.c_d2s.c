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
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  not_reached () ; 
 char* u2s (int /*<<< orphan*/ ,int,int,char*,size_t*) ; 

__attribute__((used)) static char *
d2s(intmax_t x, char sign, char *s, size_t *slen_p) {
	bool neg;

	if ((neg = (x < 0))) {
		x = -x;
	}
	s = u2s(x, 10, false, s, slen_p);
	if (neg) {
		sign = '-';
	}
	switch (sign) {
	case '-':
		if (!neg) {
			break;
		}
		/* Fall through. */
	case ' ':
	case '+':
		s--;
		(*slen_p)++;
		*s = sign;
		break;
	default: not_reached();
	}
	return s;
}