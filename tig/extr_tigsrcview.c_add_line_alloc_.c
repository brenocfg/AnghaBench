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
struct line {void* data; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 struct line* add_line (struct view*,int /*<<< orphan*/ *,int,size_t,int) ; 

struct line *
add_line_alloc_(struct view *view, void **ptr, enum line_type type, size_t data_size, bool custom)
{
	struct line *line = add_line(view, NULL, type, data_size, custom);

	if (line)
		*ptr = line->data;
	return line;
}