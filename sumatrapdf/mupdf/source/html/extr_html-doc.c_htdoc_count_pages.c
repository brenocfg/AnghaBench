#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* html; } ;
typedef  TYPE_3__ html_document ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int page_h; TYPE_1__* root; } ;
struct TYPE_4__ {int b; } ;

/* Variables and functions */
 int ceilf (int) ; 

__attribute__((used)) static int
htdoc_count_pages(fz_context *ctx, fz_document *doc_, int chapter)
{
	html_document *doc = (html_document*)doc_;
	if (doc->html->root->b > 0)
		return ceilf(doc->html->root->b / doc->html->page_h);
	return 1;
}