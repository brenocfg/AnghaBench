#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* html; } ;
typedef  TYPE_1__ html_document ;
typedef  int /*<<< orphan*/  fz_location ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {float page_h; } ;

/* Variables and functions */
 float fz_find_html_target (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  fz_make_location (int,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static fz_location
htdoc_resolve_link(fz_context *ctx, fz_document *doc_, const char *dest, float *xp, float *yp)
{
	html_document *doc = (html_document*)doc_;
	const char *s = strchr(dest, '#');
	if (s && s[1] != 0)
	{
		float y = fz_find_html_target(ctx, doc->html, s+1);
		if (y >= 0)
		{
			int page = y / doc->html->page_h;
			if (yp) *yp = y - page * doc->html->page_h;
			return fz_make_location(0, page);
		}
	}

	return fz_make_location(-1, -1);
}