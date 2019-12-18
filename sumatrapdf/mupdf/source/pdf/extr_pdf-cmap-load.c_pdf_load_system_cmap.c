#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* usecmap_name; int /*<<< orphan*/  usecmap; } ;
typedef  TYPE_1__ pdf_cmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* pdf_load_builtin_cmap (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pdf_set_usecmap (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

pdf_cmap *
pdf_load_system_cmap(fz_context *ctx, const char *cmap_name)
{
	pdf_cmap *usecmap;
	pdf_cmap *cmap;

	cmap = pdf_load_builtin_cmap(ctx, cmap_name);
	if (!cmap)
		fz_throw(ctx, FZ_ERROR_GENERIC, "no builtin cmap file: %s", cmap_name);

	if (cmap->usecmap_name[0] && !cmap->usecmap)
	{
		usecmap = pdf_load_system_cmap(ctx, cmap->usecmap_name);
		if (!usecmap)
			fz_throw(ctx, FZ_ERROR_GENERIC, "no builtin cmap file: %s", cmap->usecmap_name);
		pdf_set_usecmap(ctx, cmap, usecmap);
	}

	return cmap;
}