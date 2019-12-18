#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_11__ {int /*<<< orphan*/ * ctx; } ;
struct TYPE_10__ {TYPE_3__* doc; } ;
struct TYPE_9__ {float zoom; int area_valid; int /*<<< orphan*/  thread; void* cookie; int /*<<< orphan*/ * progress; int /*<<< orphan*/  area; int /*<<< orphan*/  const* bitmap; TYPE_2__* page; } ;
typedef  int /*<<< orphan*/  MuOfficeRenderProgressFn ;
typedef  int /*<<< orphan*/  MuOfficeRenderArea ;
typedef  TYPE_1__ MuOfficeRender ;
typedef  TYPE_2__ MuOfficePage ;
typedef  TYPE_3__ MuOfficeDoc ;
typedef  int /*<<< orphan*/  MuOfficeBitmap ;
typedef  int /*<<< orphan*/  MuError ;

/* Variables and functions */
 int /*<<< orphan*/  MuError_BadNull ; 
 int /*<<< orphan*/  MuError_OK ; 
 int /*<<< orphan*/  MuError_OOM ; 
 TYPE_1__* Pal_Mem_calloc (int,int) ; 
 int /*<<< orphan*/  Pal_Mem_free (TYPE_1__*) ; 
 scalar_t__ mu_create_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  render_worker ; 

MuError MuOfficePage_render(	MuOfficePage             *page,
				float                     zoom,
			const	MuOfficeBitmap           *bitmap,
			const	MuOfficeRenderArea       *area,
				MuOfficeRenderProgressFn *progressFn,
				void                     *cookie,
				MuOfficeRender          **pRender)
{
	MuOfficeRender *render;
	MuOfficeDoc *doc;
	fz_context *ctx;

	if (!pRender)
		return MuError_BadNull;
	*pRender = NULL;
	if (!page)
		return MuError_BadNull;
	doc = page->doc;
	ctx = doc->ctx;

	render = Pal_Mem_calloc(1, sizeof(*render));
	if (render == NULL)
		return MuError_OOM;

	render->page = page;
	render->zoom = zoom;
	render->bitmap = bitmap;
	if (area)
	{
		render->area = *area;
		render->area_valid = 1;
	}
	else
	{
		render->area_valid = 0;
	}
	render->progress = progressFn;
	render->cookie = cookie;

	if (mu_create_thread(&render->thread, render_worker, render))
	{
		Pal_Mem_free(render);
		return MuError_OOM;
	}

	*pRender = render;

	return MuError_OK;
}