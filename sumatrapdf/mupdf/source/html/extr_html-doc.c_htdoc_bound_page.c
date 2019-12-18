#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* doc; } ;
typedef  TYPE_2__ html_page ;
struct TYPE_8__ {TYPE_1__* html; } ;
typedef  TYPE_3__ html_document ;
struct TYPE_9__ {scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_4__ fz_rect ;
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {scalar_t__* page_margin; scalar_t__ page_h; scalar_t__ page_w; } ;

/* Variables and functions */
 size_t B ; 
 size_t L ; 
 size_t R ; 
 size_t T ; 

__attribute__((used)) static fz_rect
htdoc_bound_page(fz_context *ctx, fz_page *page_)
{
	html_page *page = (html_page*)page_;
	html_document *doc = page->doc;
	fz_rect bbox;
	bbox.x0 = 0;
	bbox.y0 = 0;
	bbox.x1 = doc->html->page_w + doc->html->page_margin[L] + doc->html->page_margin[R];
	bbox.y1 = doc->html->page_h + doc->html->page_margin[T] + doc->html->page_margin[B];
	return bbox;
}