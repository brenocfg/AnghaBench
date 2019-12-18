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
 char* bigbuffer ; 
 int rand () ; 

void randomize_buffer(int block_size) {
	int i;
	char rnd = rand() & 0xff;
	for (i = 0; i < block_size; i++)
		bigbuffer[i] ^= rnd;
}