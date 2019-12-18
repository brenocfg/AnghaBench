#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_get_bound_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

pdf_obj *pdf_dict_put_dict(fz_context *ctx, pdf_obj *dict, pdf_obj *key, int initial)
{
	pdf_obj *obj = pdf_new_dict(ctx, pdf_get_bound_document(ctx, dict), initial);
	pdf_dict_put_drop(ctx, dict, key, obj);
	return obj;
}