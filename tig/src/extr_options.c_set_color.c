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
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  color_map ; 
 scalar_t__ map_enum (int*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ parse_int (int*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 scalar_t__ string_isnumber (char const*) ; 

__attribute__((used)) static bool
set_color(int *color, const char *name)
{
	if (map_enum(color, color_map, name))
		return true;
	/* Git expects a plain int w/o prefix, however, color<int> is
	 * the preferred Tig color notation.  */
	if (!prefixcmp(name, "color"))
		name += 5;
	return string_isnumber(name) &&
	       parse_int(color, name, 0, 255) == SUCCESS;
}