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
struct TYPE_3__ {scalar_t__ annotations_list; int /*<<< orphan*/  ctx; scalar_t__ page_list; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_cookie ;

/* Variables and functions */
 int /*<<< orphan*/  fz_run_display_list (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdfapp_runpage(pdfapp_t *app, fz_device *dev, const fz_matrix ctm, fz_rect scissor, fz_cookie *cookie)
{
	if (app->page_list)
		fz_run_display_list(app->ctx, app->page_list, dev, ctm, scissor, cookie);
	if (app->annotations_list)
		fz_run_display_list(app->ctx, app->annotations_list, dev, ctm, scissor, cookie);
}