#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * (* begin_page ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ fz_document_writer ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

fz_device *
fz_begin_page(fz_context *ctx, fz_document_writer *wri, fz_rect mediabox)
{
	if (!wri)
		return NULL;
	if (wri->dev)
		fz_throw(ctx, FZ_ERROR_GENERIC, "called begin page without ending the previous page");
	wri->dev = wri->begin_page(ctx, wri, mediabox);
	return wri->dev;
}