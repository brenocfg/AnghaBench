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
typedef  int /*<<< orphan*/  fz_store_drop_fn ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* fz_find_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_obj_store_type ; 

void *
pdf_find_item(fz_context *ctx, fz_store_drop_fn *drop, pdf_obj *key)
{
	return fz_find_item(ctx, drop, key, &pdf_obj_store_type);
}