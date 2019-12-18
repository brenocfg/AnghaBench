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

/* Variables and functions */

__attribute__((used)) static inline int chmc_encint_len ( const UInt32 val ) {
	int len;

	// FIXME should support 64 bit?
	if ( val > 0xfffffffUL )
		len = 0; // overflow
	else if ( val > 0x1fffffUL )
		len = 4;
	else if ( val > 0x3fffUL )
		len = 3;
	else if ( val > 0x7fUL )
		len = 2;
	else
		len = 1;

	return len;
}