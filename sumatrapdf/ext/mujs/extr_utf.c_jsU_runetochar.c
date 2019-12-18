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
typedef  int Rune ;

/* Variables and functions */
 int Bitx ; 
 int Maskx ; 
 int Rune1 ; 
 int Rune2 ; 
 int T2 ; 
 int T3 ; 
 int Tx ; 

int
runetochar(char *str, const Rune *rune)
{
	int c;

	/*
	 * one character sequence
	 *	00000-0007F => 00-7F
	 */
	c = *rune;
	if(c <= Rune1) {
		str[0] = c;
		return 1;
	}

	/*
	 * two character sequence
	 *	0080-07FF => T2 Tx
	 */
	if(c <= Rune2) {
		str[0] = T2 | (c >> 1*Bitx);
		str[1] = Tx | (c & Maskx);
		return 2;
	}

	/*
	 * three character sequence
	 *	0800-FFFF => T3 Tx Tx
	 */
	str[0] = T3 |  (c >> 2*Bitx);
	str[1] = Tx | ((c >> 1*Bitx) & Maskx);
	str[2] = Tx |  (c & Maskx);
	return 3;
}