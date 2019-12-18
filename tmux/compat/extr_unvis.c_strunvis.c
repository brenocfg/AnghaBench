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
 int /*<<< orphan*/  UNVIS_END ; 
#define  UNVIS_NOCHAR 130 
#define  UNVIS_VALID 129 
#define  UNVIS_VALIDPUSH 128 
 int const unvis (char*,char,int*,int /*<<< orphan*/ ) ; 

int
strunvis(char *dst, const char *src)
{
	char c;
	char *start = dst;
	int state = 0;

	while ((c = *src++)) {
	again:
		switch (unvis(dst, c, &state, 0)) {
		case UNVIS_VALID:
			dst++;
			break;
		case UNVIS_VALIDPUSH:
			dst++;
			goto again;
		case 0:
		case UNVIS_NOCHAR:
			break;
		default:
			*dst = '\0';
			return (-1);
		}
	}
	if (unvis(dst, c, &state, UNVIS_END) == UNVIS_VALID)
		dst++;
	*dst = '\0';
	return (dst - start);
}