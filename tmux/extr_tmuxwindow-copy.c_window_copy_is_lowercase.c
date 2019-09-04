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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 char const tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
window_copy_is_lowercase(const char *ptr)
{
	while (*ptr != '\0') {
		if (*ptr != tolower((u_char)*ptr))
			return (0);
		++ptr;
	}
	return (1);
}