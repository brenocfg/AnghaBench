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
 int NUM_LARGE ; 
 int NUM_LEFT ; 
 int NUM_PLUS ; 
 int NUM_SIGN ; 
 int NUM_SPACE ; 
 int NUM_SPECIAL ; 
 int NUM_ZEROPAD ; 
 size_t do_div (long,int) ; 

__attribute__((used)) static char * PICE_number(char * str, long num, int base, int size, int precision
	,int type)
{
	char c,sign,tmp[66];
	const char *digits="0123456789abcdefghijklmnopqrstuvwxyz";
	int i;

	if (type & NUM_LARGE)
		digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (type & NUM_LEFT)
		type &= ~NUM_ZEROPAD;
	if (base < 2 || base > 36)
		return 0;
	c = (type & NUM_ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & NUM_SIGN) {
		if (num < 0) {
			sign = '-';
			num = -num;
			size--;
		} else if (type & NUM_PLUS) {
			sign = '+';
			size--;
		} else if (type & NUM_SPACE) {
			sign = ' ';
			size--;
		}
	}
	if (type & NUM_SPECIAL) {
		if (base == 16)
			size -= 2;
		else if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++]='0';
	else while (num != 0)
		tmp[i++] = digits[do_div(num,base)];
	if (i > precision)
		precision = i;
	size -= precision;
	if (!(type&(NUM_ZEROPAD+NUM_LEFT)))
		while(size-->0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	if (type & NUM_SPECIAL) {
		if (base==8)
			*str++ = '0';
		else if (base==16) {
			*str++ = '0';
			*str++ = digits[33];
		}
	}
	if (!(type & NUM_LEFT))
		while (size-- > 0)
			*str++ = c;
	while (i < precision--)
		*str++ = '0';
	while (i-- > 0)
		*str++ = tmp[i];
	while (size-- > 0)
		*str++ = ' ';
	return str;
}