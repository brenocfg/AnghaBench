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
struct TYPE_4__ {int /*<<< orphan*/  (* end_page ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ fz_document_writer ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

void
fz_end_page(fz_context *ctx, fz_document_writer *wri)
{
	fz_device *dev;

	if (!wri)
		return;
	dev = wri->dev;
	wri->dev = NULL;
	wri->end_page(ctx, wri, dev);
}