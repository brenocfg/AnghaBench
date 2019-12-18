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
 int /*<<< orphan*/ * pdf_dict_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

pdf_obj *
pdf_dict_getsa(fz_context *ctx, pdf_obj *obj, const char *key, const char *abbrev)
{
	pdf_obj *v;
	v = pdf_dict_gets(ctx, obj, key);
	if (v)
		return v;
	return pdf_dict_gets(ctx, obj, abbrev);
}