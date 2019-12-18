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
struct view {int dummy; } ;
struct keymap {int dummy; } ;
struct help {struct keymap* keymap; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int /*<<< orphan*/  add_line_alloc (struct view*,struct help**,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
add_help_line(struct view *view, struct help **help_ptr, struct keymap *keymap, enum line_type type)
{
	struct help *help;

	if (!add_line_alloc(view, &help, type, 0, false))
		return false;
	help->keymap = keymap;
	if (help_ptr)
		*help_ptr = help;
	return true;
}