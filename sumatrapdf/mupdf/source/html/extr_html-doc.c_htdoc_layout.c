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
struct TYPE_2__ {int /*<<< orphan*/  outline; int /*<<< orphan*/  html; } ;
typedef  TYPE_1__ html_document ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_layout_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,float,float) ; 
 int /*<<< orphan*/  htdoc_update_outline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
htdoc_layout(fz_context *ctx, fz_document *doc_, float w, float h, float em)
{
	html_document *doc = (html_document*)doc_;

	fz_layout_html(ctx, doc->html, w, h, em);

	htdoc_update_outline(ctx, doc_, doc->outline);
}