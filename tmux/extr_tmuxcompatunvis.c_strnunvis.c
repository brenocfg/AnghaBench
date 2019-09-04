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
 int /*<<< orphan*/  UNVIS_END ; 
#define  UNVIS_NOCHAR 130 
#define  UNVIS_VALID 129 
#define  UNVIS_VALIDPUSH 128 
 int const unvis (char*,char,int*,int /*<<< orphan*/ ) ; 

ssize_t
strnunvis(char *dst, const char *src, size_t sz)
{
	char c, p;
	char *start = dst, *end = dst + sz - 1;
	int state = 0;

	if (sz > 0)
		*end = '\0';
	while ((c = *src++)) {
	again:
		switch (unvis(&p, c, &state, 0)) {
		case UNVIS_VALID:
			if (dst < end)
				*dst = p;
			dst++;
			break;
		case UNVIS_VALIDPUSH:
			if (dst < end)
				*dst = p;
			dst++;
			goto again;
		case 0:
		case UNVIS_NOCHAR:
			break;
		default:
			if (dst <= end)
				*dst = '\0';
			return (-1);
		}
	}
	if (unvis(&p, c, &state, UNVIS_END) == UNVIS_VALID) {
		if (dst < end)
			*dst = p;
		dst++;
	}
	if (dst <= end)
		*dst = '\0';
	return (dst - start);
}