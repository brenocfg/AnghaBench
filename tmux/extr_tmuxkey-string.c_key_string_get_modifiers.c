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
typedef  scalar_t__ key_code ;

/* Variables and functions */
 scalar_t__ KEYC_CTRL ; 
 scalar_t__ KEYC_ESCAPE ; 
 scalar_t__ KEYC_SHIFT ; 

__attribute__((used)) static key_code
key_string_get_modifiers(const char **string)
{
	key_code	modifiers;

	modifiers = 0;
	while (((*string)[0] != '\0') && (*string)[1] == '-') {
		switch ((*string)[0]) {
		case 'C':
		case 'c':
			modifiers |= KEYC_CTRL;
			break;
		case 'M':
		case 'm':
			modifiers |= KEYC_ESCAPE;
			break;
		case 'S':
		case 's':
			modifiers |= KEYC_SHIFT;
			break;
		default:
			*string = NULL;
			return (0);
		}
		*string += 2;
	}
	return (modifiers);
}