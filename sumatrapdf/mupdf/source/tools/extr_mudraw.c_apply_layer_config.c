#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ depth; scalar_t__ type; char* text; scalar_t__ locked; scalar_t__ selected; } ;
typedef  TYPE_1__ pdf_layer_config_ui ;
struct TYPE_6__ {char* name; char* creator; } ;
typedef  TYPE_2__ pdf_layer_config ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ PDF_LAYER_UI_CHECKBOX ; 
 scalar_t__ PDF_LAYER_UI_LABEL ; 
 scalar_t__ PDF_LAYER_UI_RADIOBOX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fz_atoi (char const*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ iswhite (char const) ; 
 int pdf_count_layer_config_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_count_layer_configs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_layer_config_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  pdf_layer_config_ui_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_select_layer_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_specifics (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_toggle_layer_config_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void apply_layer_config(fz_context *ctx, fz_document *doc, const char *lc)
{
#if FZ_ENABLE_PDF
	pdf_document *pdoc = pdf_specifics(ctx, doc);
	int config;
	int n, j;
	pdf_layer_config info;

	if (!pdoc)
	{
		fz_warn(ctx, "Only PDF files have layers");
		return;
	}

	while (iswhite(*lc))
		lc++;

	if (*lc == 0 || *lc == 'l')
	{
		int num_configs = pdf_count_layer_configs(ctx, pdoc);

		fprintf(stderr, "Layer configs:\n");
		for (config = 0; config < num_configs; config++)
		{
			fprintf(stderr, " %s%d:", config < 10 ? " " : "", config);
			pdf_layer_config_info(ctx, pdoc, config, &info);
			if (info.name)
				fprintf(stderr, " Name=\"%s\"", info.name);
			if (info.creator)
				fprintf(stderr, " Creator=\"%s\"", info.creator);
			fprintf(stderr, "\n");
		}
		return;
	}

	/* Read the config number */
	if (*lc < '0' || *lc > '9')
	{
		fprintf(stderr, "cannot find number expected for -y\n");
		return;
	}
	config = fz_atoi(lc);
	pdf_select_layer_config(ctx, pdoc, config);

	while (*lc)
	{
		int item;

		/* Skip over the last number we read (in the fz_atoi) */
		while (*lc >= '0' && *lc <= '9')
			lc++;
		while (iswhite(*lc))
			lc++;
		if (*lc != ',')
			break;
		lc++;
		while (iswhite(*lc))
			lc++;
		if (*lc < '0' || *lc > '9')
		{
			fprintf(stderr, "Expected a number for UI item to toggle\n");
			return;
		}
		item = fz_atoi(lc);
		pdf_toggle_layer_config_ui(ctx, pdoc, item);
	}

	/* Now list the final state of the config */
	fprintf(stderr, "Layer Config %d:\n", config);
	pdf_layer_config_info(ctx, pdoc, config, &info);
	if (info.name)
		fprintf(stderr, " Name=\"%s\"", info.name);
	if (info.creator)
		fprintf(stderr, " Creator=\"%s\"", info.creator);
	fprintf(stderr, "\n");
	n = pdf_count_layer_config_ui(ctx, pdoc);
	for (j = 0; j < n; j++)
	{
		pdf_layer_config_ui ui;

		pdf_layer_config_ui_info(ctx, pdoc, j, &ui);
		fprintf(stderr, "%s%d: ", j < 10 ? " " : "", j);
		while (ui.depth > 0)
		{
			ui.depth--;
			fprintf(stderr, "  ");
		}
		if (ui.type == PDF_LAYER_UI_CHECKBOX)
			fprintf(stderr, " [%c] ", ui.selected ? 'x' : ' ');
		else if (ui.type == PDF_LAYER_UI_RADIOBOX)
			fprintf(stderr, " (%c) ", ui.selected ? 'x' : ' ');
		if (ui.text)
			fprintf(stderr, "%s", ui.text);
		if (ui.type != PDF_LAYER_UI_LABEL && ui.locked)
			fprintf(stderr, " <locked>");
		fprintf(stderr, "\n");
	}
#endif
}