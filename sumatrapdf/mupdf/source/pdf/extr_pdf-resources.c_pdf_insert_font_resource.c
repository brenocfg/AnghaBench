#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_4__ {int /*<<< orphan*/  fonts; } ;
struct TYPE_5__ {TYPE_1__ resources; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_hash_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pdf_keep_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_insert_font_resource(fz_context *ctx, pdf_document *doc, unsigned char digest[16], pdf_obj *obj)
{
	pdf_obj *res = fz_hash_insert(ctx, doc->resources.fonts, digest, obj);
	if (res)
		fz_warn(ctx, "warning: font resource already present");
	else
		res = pdf_keep_obj(ctx, obj);
	return pdf_keep_obj(ctx, res);
}