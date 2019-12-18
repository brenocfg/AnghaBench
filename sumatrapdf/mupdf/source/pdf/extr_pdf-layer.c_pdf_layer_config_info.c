#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_8__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * creator; } ;
typedef  TYPE_2__ pdf_layer_config ;
struct TYPE_9__ {TYPE_1__* ocg; } ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {int num_configs; } ;

/* Variables and functions */
 int /*<<< orphan*/  Configs ; 
 int /*<<< orphan*/  Creator ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  Name ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pdf_dict_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,TYPE_3__*) ; 

void
pdf_layer_config_info(fz_context *ctx, pdf_document *doc, int config_num, pdf_layer_config *info)
{
	pdf_obj *ocprops;
	pdf_obj *obj;

	if (!info)
		return;

	info->name = NULL;
	info->creator = NULL;

	if (doc == NULL || doc->ocg == NULL)
		return;
	if (config_num < 0 || config_num >= doc->ocg->num_configs)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Invalid layer config number");

	ocprops = pdf_dict_getp(ctx, pdf_trailer(ctx, doc), "Root/OCProperties");
	if (!ocprops)
		return;

	obj = pdf_dict_get(ctx, ocprops, PDF_NAME(Configs));
	if (pdf_is_array(ctx, obj))
		obj = pdf_array_get(ctx, obj, config_num);
	else if (config_num == 0)
		obj = pdf_dict_get(ctx, ocprops, PDF_NAME(D));
	else
		fz_throw(ctx, FZ_ERROR_GENERIC, "Invalid layer config number");

	info->creator = pdf_dict_get_string(ctx, obj, PDF_NAME(Creator), NULL);
	info->name = pdf_dict_get_string(ctx, obj, PDF_NAME(Name), NULL);
}