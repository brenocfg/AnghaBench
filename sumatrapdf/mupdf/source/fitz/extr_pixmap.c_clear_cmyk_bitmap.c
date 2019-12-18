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
typedef  unsigned char uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  clear_cmyka_bitmap_ARM (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
clear_cmyk_bitmap(unsigned char *samples, int w, int h, int spots, int stride, int value, int alpha)
{
	uint32_t *s = (uint32_t *)(void *)samples;
	uint8_t *t;

	if (w < 0 || h < 0)
		return;

	if (spots)
	{
		int x, i;
		spots += 4;
		stride -= w * (spots + alpha);
		for (; h > 0; h--)
		{
			for (x = w; x > 0; x--)
			{
				for (i = spots; i > 0; i--)
					*samples++ = value;
				if (alpha)
					*samples++ = 255;
			}
			samples += stride;
		}
		return;
	}

	if (alpha)
	{
		int c = w;
		stride -= w*5;
		if (stride == 0)
		{
#ifdef ARCH_ARM
			clear_cmyka_bitmap_ARM(s, c, alpha);
			return;
#else
			/* We can do it all fast (except for maybe a few stragglers) */
			union
			{
				uint8_t bytes[20];
				uint32_t words[5];
			} d;

			c *= h;
			h = 1;

			d.words[0] = 0;
			d.words[1] = 0;
			d.words[2] = 0;
			d.words[3] = 0;
			d.words[4] = 0;
			d.bytes[3] = value;
			d.bytes[4] = 255;
			d.bytes[8] = value;
			d.bytes[9] = 255;
			d.bytes[13] = value;
			d.bytes[14] = 255;
			d.bytes[18] = value;
			d.bytes[19] = 255;

			c -= 3;
			{
				const uint32_t a0 = d.words[0];
				const uint32_t a1 = d.words[1];
				const uint32_t a2 = d.words[2];
				const uint32_t a3 = d.words[3];
				const uint32_t a4 = d.words[4];
				while (c > 0)
				{
					*s++ = a0;
					*s++ = a1;
					*s++ = a2;
					*s++ = a3;
					*s++ = a4;
					c -= 4;
				}
			}
			c += 3;
#endif
		}
		t = (unsigned char *)s;
		w = c;
		while (h--)
		{
			c = w;
			while (c > 0)
			{
				*t++ = 0;
				*t++ = 0;
				*t++ = 0;
				*t++ = value;
				*t++ = 255;
				c--;
			}
			t += stride;
		}
	}
	else
	{
		stride -= w*4;
		if ((stride & 3) == 0)
		{
			size_t W = w;
			if (stride == 0)
			{
				W *= h;
				h = 1;
			}
			W *= 4;
			if (value == 0)
			{
				while (h--)
				{
					memset(s, 0, W);
					s += (stride>>2);
				}
			}
			else
			{
				/* We can do it all fast */
				union
				{
					uint8_t bytes[4];
					uint32_t word;
				} d;

				d.word = 0;
				d.bytes[3] = value;
				{
					const uint32_t a0 = d.word;
					while (h--)
					{
						size_t WW = W >> 2;
						while (WW--)
						{
							*s++ = a0;
						}
						s += (stride>>2);
					}
				}
			}
		}
		else
		{
			t = (unsigned char *)s;
			while (h--)
			{
				int c = w;
				while (c > 0)
				{
					*t++ = 0;
					*t++ = 0;
					*t++ = 0;
					*t++ = value;
					c--;
				}
				t += stride;
			}
		}
	}
}