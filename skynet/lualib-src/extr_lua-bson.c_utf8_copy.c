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
 unsigned int MAXUNICODE ; 

__attribute__((used)) static int
utf8_copy(const char *s, char *d, size_t limit) {
	static const unsigned int limits[] = {0xFF, 0x7F, 0x7FF, 0xFFFF};
	unsigned int c = s[0];
	unsigned int res = 0;
	if (limit < 1)
		return 0;
	d[0] = s[0];
	if (c < 0x80) {
		return 1;
	} else {
		int count = 0;
		while (c & 0x40) {
			int cc = s[++count];
			if (limit <= count || (cc & 0xC0) != 0x80)
				return 0;
			d[count] = s[count];
			res = (res << 6) | (cc & 0x3F);
			c <<= 1;
		}
		res |= ((c & 0x7F) << (count * 5));
		if (count > 3 || res > MAXUNICODE || res <= limits[count])
			return 0;
		return count+1;
	}
}