#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  html; } ;
typedef  TYPE_1__ html_document ;
struct TYPE_5__ {int /*<<< orphan*/  page; } ;
typedef  TYPE_2__ fz_location ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  fz_make_html_bookmark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_bookmark
htdoc_make_bookmark(fz_context *ctx, fz_document *doc_, fz_location loc)
{
	html_document *doc = (html_document*)doc_;
	return fz_make_html_bookmark(ctx, doc->html, loc.page);
}