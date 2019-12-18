#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int page_h; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ fz_html ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  make_box_bookmark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

fz_bookmark
fz_make_html_bookmark(fz_context *ctx, fz_html *html, int page)
{
	return (fz_bookmark)make_box_bookmark(ctx, html->root, page * html->page_h);
}