#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int category; } ;
typedef  TYPE_1__ utf8proc_property_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 TYPE_1__* utf8proc_get_property (int /*<<< orphan*/ ) ; 
 scalar_t__ utf8proc_iterate (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
utf8_string_contains(const char *text, int category)
{
	ssize_t textlen = strlen(text);

	while (textlen > 0) {
		int32_t unicode;
		ssize_t slen = utf8proc_iterate((uint8_t *) text, textlen, &unicode);
		const utf8proc_property_t *property;

		if (slen <= 0)
			break;

		property = utf8proc_get_property(unicode);
		if (property->category & category)
			return true;

		text += slen;
		textlen -= slen;
	}

	return false;
}