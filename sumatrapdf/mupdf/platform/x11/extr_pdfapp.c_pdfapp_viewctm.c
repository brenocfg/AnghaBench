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
struct TYPE_3__ {int /*<<< orphan*/  rotate; int /*<<< orphan*/  resolution; int /*<<< orphan*/  page_bbox; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  int /*<<< orphan*/  fz_matrix ;

/* Variables and functions */
 int /*<<< orphan*/  fz_transform_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdfapp_viewctm(fz_matrix *mat, pdfapp_t *app)
{
	*mat = fz_transform_page(app->page_bbox, app->resolution, app->rotate);
}