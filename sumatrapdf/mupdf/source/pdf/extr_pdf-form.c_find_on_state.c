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
 int /*<<< orphan*/  Off ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pdf_obj *find_on_state(fz_context *ctx, pdf_obj *dict)
{
	int i, n = pdf_dict_len(ctx, dict);
	for (i = 0; i < n; ++i)
	{
		pdf_obj *key = pdf_dict_get_key(ctx, dict, i);
		if (key != PDF_NAME(Off))
			return key;
	}
	return NULL;
}