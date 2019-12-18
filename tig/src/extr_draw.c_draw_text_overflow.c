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
 int LINE_OVERFLOW ; 
 int MIN (scalar_t__,int) ; 
 scalar_t__ VIEW_MAX_LEN (struct view*) ; 
 scalar_t__ draw_text (struct view*,int,char const*) ; 
 scalar_t__ draw_text_expanded (struct view*,int,char const*,int,int,int) ; 
 size_t utf8_length (char const**,int,int /*<<< orphan*/ ,int*,int,int*,int,int) ; 

__attribute__((used)) static bool
draw_text_overflow(struct view *view, const char *text, enum line_type type,
		   int overflow_length, int offset)
{
	bool on = overflow_length > 0;

	if (on) {
		int overflow = overflow_length + offset;
		int max = MIN(VIEW_MAX_LEN(view), overflow);
		const char *tmp = text;
		int text_width = 0;
		int trimmed = false;
		size_t len = utf8_length(&tmp, -1, 0, &text_width, max, &trimmed, false, 1);

		if (draw_text_expanded(view, type, text, -1, text_width, max < overflow))
			return true;

		text += len;
		type = LINE_OVERFLOW;
	}

	if (*text && draw_text(view, type, text))
		return true;

	return VIEW_MAX_LEN(view) <= 0;
}