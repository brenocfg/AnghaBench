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

__attribute__((used)) static inline int canon(int c)
{
	/* TODO: proper unicode case folding */
	/* TODO: character equivalence (a matches ä, etc) */
	if (c == 0xA0 || c == 0x2028 || c == 0x2029)
		return ' ';
	if (c == '\r' || c == '\n' || c == '\t')
		return ' ';
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 'a';
	return c;
}