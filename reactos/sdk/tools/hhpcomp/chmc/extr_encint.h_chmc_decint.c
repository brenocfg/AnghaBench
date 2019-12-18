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
typedef  int UInt32 ;
typedef  int UChar ;

/* Variables and functions */

__attribute__((used)) static inline int chmc_decint ( const UChar *in, UInt32 *value ) {
	int len;

	len = 0;
	*value = 0;

	while ( (in[len] & 0x80) && (len < 3) ) {
		*value <<= 7;
		*value |= in[len] & 0x7f;
		len++;
	}
	*value <<= 7;
	*value |= in[len] & 0x7f;
	len++;

	return len;
}