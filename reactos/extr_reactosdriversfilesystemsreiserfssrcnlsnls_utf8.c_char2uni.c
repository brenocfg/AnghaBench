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
typedef  int wchar_t ;

/* Variables and functions */
 int EINVAL ; 
 int utf8_mbtowc (int*,unsigned char const*,int) ; 

__attribute__((used)) static int char2uni(const unsigned char *rawstring, int boundlen, wchar_t *uni)
{
	int n;

	if ( (n = utf8_mbtowc(uni, rawstring, boundlen)) == -1) {
		*uni = 0x003f;	/* ? */
		n = -EINVAL;
	}
	return n;
}