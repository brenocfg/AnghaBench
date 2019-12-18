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
typedef  long __int64 ;
typedef  long ULONGLONG ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

char* _i64toa(__int64 value, char* string, int radix)
{
    ULONGLONG val;
    int negative;
    char buffer[65];
    char *pos;
    int digit;

    if (value < 0 && radix == 10) {
	negative = 1;
        val = -value;
    } else {
	negative = 0;
        val = value;
    } /* if */

    pos = &buffer[64];
    *pos = '\0';

    do {
	digit = val % radix;
	val = val / radix;
	if (digit < 10) {
	    *--pos = '0' + digit;
	} else {
	    *--pos = 'a' + digit - 10;
	} /* if */
    } while (val != 0L);

    if (negative) {
	*--pos = '-';
    } /* if */

    memcpy(string, pos, &buffer[64] - pos + 1);
    return string;
}