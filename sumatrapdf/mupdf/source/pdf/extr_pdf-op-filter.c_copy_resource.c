#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_3__ {int /*<<< orphan*/  new_rdb; int /*<<< orphan*/  old_rdb; } ;
typedef  TYPE_1__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_putp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_get_bound_document (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
copy_resource(fz_context *ctx, pdf_filter_processor *p, pdf_obj *key, const char *name)
{
	pdf_obj *res, *obj;

	if (!name || name[0] == 0)
		return;

	res = pdf_dict_get(ctx, p->old_rdb, key);
	obj = pdf_dict_gets(ctx, res, name);
	if (obj)
	{
		res = pdf_dict_get(ctx, p->new_rdb, key);
		if (!res)
		{
			res = pdf_new_dict(ctx, pdf_get_bound_document(ctx, p->new_rdb), 1);
			pdf_dict_put_drop(ctx, p->new_rdb, key, res);
		}
		pdf_dict_putp(ctx, res, name, obj);
	}
}