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
#define  S_CTRL 134 
#define  S_GROUND 133 
#define  S_META 132 
#define  S_META1 131 
#define  S_OCTAL2 130 
#define  S_OCTAL3 129 
#define  S_START 128 
 int UNVIS_END ; 
 int UNVIS_NOCHAR ; 
 int UNVIS_SYNBAD ; 
 int UNVIS_VALID ; 
 int UNVIS_VALIDPUSH ; 
 int /*<<< orphan*/  isoctal (char) ; 

int
unvis(char *cp, char c, int *astate, int flag)
{

	if (flag & UNVIS_END) {
		if (*astate == S_OCTAL2 || *astate == S_OCTAL3) {
			*astate = S_GROUND;
			return (UNVIS_VALID);
		}
		return (*astate == S_GROUND ? UNVIS_NOCHAR : UNVIS_SYNBAD);
	}

	switch (*astate) {

	case S_GROUND:
		*cp = 0;
		if (c == '\\') {
			*astate = S_START;
			return (0);
		}
		*cp = c;
		return (UNVIS_VALID);

	case S_START:
		switch(c) {
		case '\\':
			*cp = c;
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			*cp = (c - '0');
			*astate = S_OCTAL2;
			return (0);
		case 'M':
			*cp = (char) 0200;
			*astate = S_META;
			return (0);
		case '^':
			*astate = S_CTRL;
			return (0);
		case 'n':
			*cp = '\n';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'r':
			*cp = '\r';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'b':
			*cp = '\b';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'a':
			*cp = '\007';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'v':
			*cp = '\v';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 't':
			*cp = '\t';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'f':
			*cp = '\f';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 's':
			*cp = ' ';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case 'E':
			*cp = '\033';
			*astate = S_GROUND;
			return (UNVIS_VALID);
		case '\n':
			/*
			 * hidden newline
			 */
			*astate = S_GROUND;
			return (UNVIS_NOCHAR);
		case '$':
			/*
			 * hidden marker
			 */
			*astate = S_GROUND;
			return (UNVIS_NOCHAR);
		}
		*astate = S_GROUND;
		return (UNVIS_SYNBAD);

	case S_META:
		if (c == '-')
			*astate = S_META1;
		else if (c == '^')
			*astate = S_CTRL;
		else {
			*astate = S_GROUND;
			return (UNVIS_SYNBAD);
		}
		return (0);

	case S_META1:
		*astate = S_GROUND;
		*cp |= c;
		return (UNVIS_VALID);

	case S_CTRL:
		if (c == '?')
			*cp |= 0177;
		else
			*cp |= c & 037;
		*astate = S_GROUND;
		return (UNVIS_VALID);

	case S_OCTAL2:	/* second possible octal digit */
		if (isoctal(c)) {
			/*
			 * yes - and maybe a third
			 */
			*cp = (*cp << 3) + (c - '0');
			*astate = S_OCTAL3;
			return (0);
		}
		/*
		 * no - done with current sequence, push back passed char
		 */
		*astate = S_GROUND;
		return (UNVIS_VALIDPUSH);

	case S_OCTAL3:	/* third possible octal digit */
		*astate = S_GROUND;
		if (isoctal(c)) {
			*cp = (*cp << 3) + (c - '0');
			return (UNVIS_VALID);
		}
		/*
		 * we were done, push back passed char
		 */
		return (UNVIS_VALIDPUSH);

	default:
		/*
		 * decoder in unknown state - (probably uninitialized)
		 */
		*astate = S_GROUND;
		return (UNVIS_SYNBAD);
	}
}