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
typedef  int uint8_t ;

/* Variables and functions */
 int SIZEOF_LENGTH ; 

__attribute__((used)) static inline int
fill_size(uint8_t * data, int sz) {
	data[0] = sz & 0xff;
	data[1] = (sz >> 8) & 0xff;
	data[2] = (sz >> 16) & 0xff;
	data[3] = (sz >> 24) & 0xff;
	return sz + SIZEOF_LENGTH;
}