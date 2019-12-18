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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  valid_char (char,int /*<<< orphan*/ ) ; 

boolean_t
zfeature_is_valid_guid(const char *name)
{
	int i;
	boolean_t has_colon = B_FALSE;

	i = 0;
	while (name[i] != '\0') {
		char c = name[i++];
		if (c == ':') {
			if (has_colon)
				return (B_FALSE);
			has_colon = B_TRUE;
			continue;
		}
		if (!valid_char(c, has_colon))
			return (B_FALSE);
	}

	return (has_colon);
}