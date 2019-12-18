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
typedef  int /*<<< orphan*/  pdf_page ;
typedef  int /*<<< orphan*/  fz_page_bound_page_fn ;
struct TYPE_3__ {int /*<<< orphan*/ * bound_page; } ;
typedef  TYPE_1__ fz_page ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ pdf_bound_page ; 

pdf_page *pdf_page_from_fz_page(fz_context *ctx, fz_page *ptr)
{
	return (pdf_page *)((ptr && ptr->bound_page == (fz_page_bound_page_fn*)pdf_bound_page) ? ptr : NULL);
}