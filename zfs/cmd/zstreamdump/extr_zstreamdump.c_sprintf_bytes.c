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
typedef  int uint_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static void
sprintf_bytes(char *str, uint8_t *buf, uint_t buf_len)
{
	int i, n;

	for (i = 0; i < buf_len; i++) {
		n = sprintf(str, "%02x", buf[i] & 0xff);
		str += n;
	}

	str[0] = '\0';
}