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
struct TYPE_3__ {int /*<<< orphan*/  image; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  int /*<<< orphan*/  fz_rect ;

/* Variables and functions */
 int /*<<< orphan*/  fz_invert_pixmap_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_round_rect (int /*<<< orphan*/ ) ; 

void pdfapp_invert(pdfapp_t *app, fz_rect rect)
{
	fz_invert_pixmap_rect(app->ctx, app->image, fz_round_rect(rect));
}