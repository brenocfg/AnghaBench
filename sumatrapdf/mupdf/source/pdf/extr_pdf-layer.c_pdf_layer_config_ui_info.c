#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t ocg; int /*<<< orphan*/ * name; int /*<<< orphan*/  locked; int /*<<< orphan*/  depth; int /*<<< orphan*/  button_flags; } ;
typedef  TYPE_3__ pdf_ocg_ui ;
struct TYPE_11__ {int /*<<< orphan*/ * text; int /*<<< orphan*/  locked; int /*<<< orphan*/  selected; int /*<<< orphan*/  depth; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ pdf_layer_config_ui ;
struct TYPE_12__ {TYPE_2__* ocg; } ;
typedef  TYPE_5__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {int num_ui_entries; TYPE_1__* ocgs; TYPE_3__* ui; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
pdf_layer_config_ui_info(fz_context *ctx, pdf_document *doc, int ui, pdf_layer_config_ui *info)
{
	pdf_ocg_ui *entry;

	if (!info)
		return;

	info->depth = 0;
	info->locked = 0;
	info->selected = 0;
	info->text = NULL;
	info->type = 0;

	if (doc == NULL || doc->ocg == NULL)
		return;

	if (ui < 0 || ui >= doc->ocg->num_ui_entries)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Out of range UI entry selected");

	entry = &doc->ocg->ui[ui];
	info->type = entry->button_flags;
	info->depth = entry->depth;
	info->selected = doc->ocg->ocgs[entry->ocg].state;
	info->locked = entry->locked;
	info->text = entry->name;
}