#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int hit_count; int /*<<< orphan*/ * hit_bbox; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;

/* Variables and functions */
 int /*<<< orphan*/  fz_rect_from_quad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdfapp_invert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdfapp_viewctm (int /*<<< orphan*/ *,TYPE_1__*) ; 

void pdfapp_inverthit(pdfapp_t *app)
{
	fz_rect bbox;
	fz_matrix ctm;
	int i;

	pdfapp_viewctm(&ctm, app);

	for (i = 0; i < app->hit_count; i++)
	{
		bbox = fz_rect_from_quad(app->hit_bbox[i]);
		bbox = fz_transform_rect(bbox, ctm);
		pdfapp_invert(app, bbox);
	}
}