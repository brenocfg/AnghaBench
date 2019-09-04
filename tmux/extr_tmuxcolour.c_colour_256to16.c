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
typedef  int u_char ;

/* Variables and functions */

u_char
colour_256to16(u_char c)
{
	static const u_char table[256] = {
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
		 0,  4,  4,  4, 12, 12,  2,  6,  4,  4, 12, 12,  2,  2,  6,  4,
		12, 12,  2,  2,  2,  6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10,
		10, 10, 10, 14,  1,  5,  4,  4, 12, 12,  3,  8,  4,  4, 12, 12,
		 2,  2,  6,  4, 12, 12,  2,  2,  2,  6, 12, 12, 10, 10, 10, 10,
		14, 12, 10, 10, 10, 10, 10, 14,  1,  1,  5,  4, 12, 12,  1,  1,
		 5,  4, 12, 12,  3,  3,  8,  4, 12, 12,  2,  2,  2,  6, 12, 12,
		10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14,  1,  1,  1,  5,
		12, 12,  1,  1,  1,  5, 12, 12,  1,  1,  1,  5, 12, 12,  3,  3,
		 3,  7, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14,
		 9,  9,  9,  9, 13, 12,  9,  9,  9,  9, 13, 12,  9,  9,  9,  9,
		13, 12,  9,  9,  9,  9, 13, 12, 11, 11, 11, 11,  7, 12, 10, 10,
		10, 10, 10, 14,  9,  9,  9,  9,  9, 13,  9,  9,  9,  9,  9, 13,
		 9,  9,  9,  9,  9, 13,  9,  9,  9,  9,  9, 13,  9,  9,  9,  9,
		 9, 13, 11, 11, 11, 11, 11, 15,  0,  0,  0,  0,  0,  0,  8,  8,
		 8,  8,  8,  8,  7,  7,  7,  7,  7,  7, 15, 15, 15, 15, 15, 15
	};

	return (table[c]);
}