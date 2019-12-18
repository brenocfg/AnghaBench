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
 int /*<<< orphan*/  toggleUniKey (unsigned long,int) ; 
 int /*<<< orphan*/  toggleUnicodeKey (unsigned long,int) ; 

void typeString(const char *str)
{
	unsigned short c;
	unsigned short c1;
	unsigned short c2;
	unsigned short c3;
	unsigned long n;

	while (*str != '\0') {
		c = *str++;

		// warning, the following utf8 decoder
		// doesn't perform validation
		if (c <= 0x7F) {
			// 0xxxxxxx one byte
			n = c;
		} else if ((c & 0xE0) == 0xC0)  {
			// 110xxxxx two bytes
			c1 = (*str++) & 0x3F;
			n = ((c & 0x1F) << 6) | c1;
		} else if ((c & 0xF0) == 0xE0) {
			// 1110xxxx three bytes
			c1 = (*str++) & 0x3F;
			c2 = (*str++) & 0x3F;
			n = ((c & 0x0F) << 12) | (c1 << 6) | c2;
		} else if ((c & 0xF8) == 0xF0) {
			// 11110xxx four bytes
			c1 = (*str++) & 0x3F;
			c2 = (*str++) & 0x3F;
			c3 = (*str++) & 0x3F;
			n = ((c & 0x07) << 18) | (c1 << 12) | (c2 << 6) | c3;
		}

		#if defined(IS_MACOSX)
		toggleUnicodeKey(n, true);
		toggleUnicodeKey(n, false);
		#else
		toggleUniKey(n, true);
		toggleUniKey(n, false);
		#endif

	}
}