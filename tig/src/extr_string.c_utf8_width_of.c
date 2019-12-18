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
 int /*<<< orphan*/  utf8_length (char const**,int,int /*<<< orphan*/ ,int*,int,int*,int,int) ; 

int
utf8_width_of(const char *text, int max_bytes, int max_width)
{
	int text_width = 0;
	const char *tmp = text;
	int trimmed = false;

	utf8_length(&tmp, max_bytes, 0, &text_width, max_width, &trimmed, false, 1);
	return text_width;
}