#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ button_flags; size_t ocg; scalar_t__ locked; } ;
typedef  TYPE_3__ pdf_ocg_ui ;
struct TYPE_10__ {TYPE_2__* ocg; } ;
typedef  TYPE_4__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int num_ui_entries; TYPE_1__* ocgs; TYPE_3__* ui; } ;
struct TYPE_7__ {int state; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ PDF_LAYER_UI_CHECKBOX ; 
 scalar_t__ PDF_LAYER_UI_RADIOBOX ; 
 int /*<<< orphan*/  clear_radio_group (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void pdf_select_layer_config_ui(fz_context *ctx, pdf_document *doc, int ui)
{
	pdf_ocg_ui *entry;

	if (doc == NULL || doc->ocg == NULL)
		return;

	if (ui < 0 || ui >= doc->ocg->num_ui_entries)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Out of range UI entry selected");

	entry = &doc->ocg->ui[ui];
	if (entry->button_flags != PDF_LAYER_UI_RADIOBOX &&
		entry->button_flags != PDF_LAYER_UI_CHECKBOX)
		return;
	if (entry->locked)
		return;

	if (entry->button_flags == PDF_LAYER_UI_RADIOBOX)
		clear_radio_group(ctx, doc, doc->ocg->ocgs[entry->ocg].obj);

	doc->ocg->ocgs[entry->ocg].state = 1;
}