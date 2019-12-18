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
 int /*<<< orphan*/  pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* pdf_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

const char *pdf_dict_get_string(fz_context *ctx, pdf_obj *dict, pdf_obj *key, size_t *sizep)
{
	return pdf_to_string(ctx, pdf_dict_get(ctx, dict, key), sizep);
}