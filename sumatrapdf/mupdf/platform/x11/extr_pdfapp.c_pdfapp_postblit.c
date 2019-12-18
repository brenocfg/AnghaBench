#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float duration; } ;
struct TYPE_6__ {int transitions_enabled; scalar_t__ duration; scalar_t__ in_transit; TYPE_5__ transition; int /*<<< orphan*/ * new_image; int /*<<< orphan*/ * old_image; int /*<<< orphan*/ * image; int /*<<< orphan*/  ctx; int /*<<< orphan*/  imgh; int /*<<< orphan*/  imgw; scalar_t__ start_time; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 float CLOCKS_PER_SEC ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_generate_transition (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_5__*) ; 
 int /*<<< orphan*/  fz_pixmap_height (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_pixmap_width (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  winadvancetimer (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  winrepaint (TYPE_1__*) ; 

void pdfapp_postblit(pdfapp_t *app)
{
	clock_t time;
	float seconds;
	int llama;

	app->transitions_enabled = 1;
	if (!app->in_transit)
		return;
	time = clock();
	seconds = (float)(time - app->start_time) / CLOCKS_PER_SEC;
	llama = seconds * 256 / app->transition.duration;
	if (llama >= 256)
	{
		/* Completed. */
		fz_drop_pixmap(app->ctx, app->image);
		app->image = app->new_image;
		app->new_image = NULL;
		app->imgw = fz_pixmap_width(app->ctx, app->image);
		app->imgh = fz_pixmap_height(app->ctx, app->image);
		fz_drop_pixmap(app->ctx, app->old_image);
		app->old_image = NULL;
		if (app->duration != 0)
			winadvancetimer(app, app->duration);
	}
	else
		fz_generate_transition(app->ctx, app->image, app->old_image, app->new_image, llama, &app->transition);
	winrepaint(app);
	if (llama >= 256)
	{
		/* Completed. */
		app->in_transit = 0;
	}
}