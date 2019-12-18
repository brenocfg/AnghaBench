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
 int* clz ; 
 int* mask ; 

__attribute__((used)) static inline int
find_changing(const unsigned char *line, int x, int w)
{
	int a, b, m, W;

	if (!line)
		return w;

	/* We assume w > 0, -1 <= x < w */
	if (x < 0)
	{
		x = 0;
		m = 0xFF;
	}
	else
	{
		/* Mask out the bits we've already used (including the one
		 * we started from) */
		m = mask[x & 7];
	}
	/* We have 'w' pixels (bits) in line. The last pixel that can be
	 * safely accessed is the (w-1)th bit of line.
	 * By taking W = w>>3, we know that the first W bytes of line are
	 * full, with w&7 stray bits following. */
	W = w>>3;
	x >>= 3;
	a = line[x]; /* Safe as x < w => x <= w-1 => x>>3 <= (w-1)>>3 */
	b = a ^ (a>>1);
	b &= m;
	if (x >= W)
	{
		/* Within the last byte already */
		x = (x<<3) + clz[b];
		if (x > w)
			x = w;
		return x;
	}
	while (b == 0)
	{
		if (++x >= W)
			goto nearend;
		b = a & 1;
		a = line[x];
		b = (b<<7) ^ a ^ (a>>1);
	}
	return (x<<3) + clz[b];
nearend:
	/* We have less than a byte to go. If no stray bits, exit now. */
	if ((x<<3) == w)
		return w;
	b = a&1;
	a = line[x];
	b = (b<<7) ^ a ^ (a>>1);
	x = (x<<3) + clz[b];
	if (x > w)
		x = w;
	return x;
}