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
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int /*<<< orphan*/  VIEW_MAX_LEN (struct view*) ; 
 int draw_text_expanded (struct view*,int,char const*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool
draw_textn(struct view *view, enum line_type type, const char *string, int length)
{
	return draw_text_expanded(view, type, string, length, VIEW_MAX_LEN(view), false);
}