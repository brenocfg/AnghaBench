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
typedef  int ssize_t ;

/* Variables and functions */
 size_t* encoding_widths ; 

__attribute__((used)) static unsigned char *next_text(unsigned char* prev, unsigned char encoding, size_t limit)
{
	unsigned char *text = prev;
	size_t width = encoding_widths[encoding];

	/* So I go lengths to find zero or double zero...
	   Remember bug 2834636: Only check for aligned NULLs! */
	while(text-prev < (ssize_t)limit)
	{
		if(text[0] == 0)
		{
			if(width <= limit-(text-prev))
			{
				size_t i = 1;
				for(; i<width; ++i) if(text[i] != 0) break;

				if(i == width) /* found a null wide enough! */
				{
					text += width;
					break;
				}
			}
			else return NULL; /* No full character left? This text is broken */
		}

		text += width;
	}
	if((size_t)(text-prev) >= limit) text = NULL;

	return text;
}