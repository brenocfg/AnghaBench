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
struct TYPE_5__ {int page_h; TYPE_1__* root; } ;
typedef  TYPE_2__ fz_html ;
struct TYPE_4__ {int b; } ;

/* Variables and functions */
 int ceilf (int) ; 

__attribute__((used)) static int count_laid_out_pages(fz_html *html)
{
	if (html->root->b > 0)
		return ceilf(html->root->b / html->page_h);
	return 1;
}