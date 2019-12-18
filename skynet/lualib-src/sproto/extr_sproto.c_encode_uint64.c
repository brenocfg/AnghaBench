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
typedef  int /*<<< orphan*/  v ;
typedef  int uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int SIZEOF_LENGTH ; 
 int fill_size (int*,int) ; 

__attribute__((used)) static int
encode_uint64(uint64_t v, uint8_t * data, int size) {
	if (size < SIZEOF_LENGTH + sizeof(v))
		return -1;
	data[4] = v & 0xff;
	data[5] = (v >> 8) & 0xff;
	data[6] = (v >> 16) & 0xff;
	data[7] = (v >> 24) & 0xff;
	data[8] = (v >> 32) & 0xff;
	data[9] = (v >> 40) & 0xff;
	data[10] = (v >> 48) & 0xff;
	data[11] = (v >> 56) & 0xff;
	return fill_size(data, sizeof(v));
}