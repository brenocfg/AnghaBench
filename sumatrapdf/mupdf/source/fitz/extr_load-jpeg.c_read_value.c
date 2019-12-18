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

__attribute__((used)) static inline int read_value(const unsigned char *data, int bytes, int is_big_endian)
{
	int value = 0;
	if (!is_big_endian)
		data += bytes;
	for (; bytes > 0; bytes--)
		value = (value << 8) | (is_big_endian ? *data++ : *--data);
	return value;
}