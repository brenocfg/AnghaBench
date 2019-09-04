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

__attribute__((used)) static int
LsMonthNameToNum(char *cp)
{
	int mon;	/* 0..11 */

	switch (*cp++) {
		case 'A':
			mon = (*cp == 'u') ? 7 : 3;
			break;
		case 'D':
			mon = 11;
			break;
		case 'F':
			mon = 1;
			break;
		default:
		case 'J':
			if (*cp++ == 'u')
				mon = (*cp == 'l') ? 6 : 5;
			else
				mon = 0;
			break;
		case 'M':
			mon = (*++cp == 'r') ? 2 : 4;
			break;
		case 'N':
			mon = 10;
			break;
		case 'O':
			mon = 9;
			break;
		case 'S':
			mon = 8;
	}
	return (mon);
}