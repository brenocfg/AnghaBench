#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t col; } ;
struct view {size_t col; int /*<<< orphan*/  win; TYPE_1__ pos; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 scalar_t__ ICONV_NONE ; 
 int LINE_DELIMITER ; 
 scalar_t__ VIEW_MAX_LEN (struct view*) ; 
 char* encoding_iconv (scalar_t__,char const*,int) ; 
 scalar_t__ opt_iconv_out ; 
 int /*<<< orphan*/  opt_tab_size ; 
 char* opt_truncation_delimiter ; 
 int /*<<< orphan*/  set_view_attr (struct view*,int) ; 
 int utf8_length (char const**,int,size_t,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waddnstr (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
draw_chars(struct view *view, enum line_type type, const char *string, int length,
	   int max_width, bool use_tilde)
{
	int len = 0;
	int col = 0;
	int trimmed = false;
	size_t skip = view->pos.col > view->col ? view->pos.col - view->col : 0;

	if (max_width <= 0)
		return VIEW_MAX_LEN(view) <= 0;

	len = utf8_length(&string, length, skip, &col, max_width, &trimmed, use_tilde, opt_tab_size);

	if (opt_iconv_out != ICONV_NONE) {
		string = encoding_iconv(opt_iconv_out, string, len);
		if (!string)
			return VIEW_MAX_LEN(view) <= 0;
	}

	set_view_attr(view, type);
	if (len > 0)
		waddnstr(view->win, string, len);

	if (trimmed && use_tilde) {
		set_view_attr(view, LINE_DELIMITER);
		waddstr(view->win, opt_truncation_delimiter ? opt_truncation_delimiter : "~");
		col++;
	}

	view->col += col;
	return VIEW_MAX_LEN(view) <= 0;
}