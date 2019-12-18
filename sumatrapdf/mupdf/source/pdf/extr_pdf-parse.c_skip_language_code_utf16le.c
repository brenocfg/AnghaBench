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

__attribute__((used)) static size_t
skip_language_code_utf16le(const unsigned char *s, size_t n, size_t i)
{
	/* skip language escape codes */
	if (i + 6 <= n && s[i+1] == 0 && s[i+0] == 27 && s[i+5] == 0 && s[i+4] == 27)
		return 6;
	else if (i + 8 <= n && s[i+1] == 0 && s[i+0] == 27 && s[i+7] == 0 && s[i+6] == 27)
		return 8;
	return 0;
}