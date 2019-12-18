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
 int /*<<< orphan*/  assert (int) ; 
 void* fz_store_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_obj_store_type ; 

void
pdf_store_item(fz_context *ctx, pdf_obj *key, void *val, size_t itemsize)
{
	void *existing;

	assert(pdf_is_name(ctx, key) || pdf_is_array(ctx, key) || pdf_is_dict(ctx, key) || pdf_is_indirect(ctx, key));
	existing = fz_store_item(ctx, key, val, itemsize, &pdf_obj_store_type);
	assert(existing == NULL);
	(void)existing; /* Silence warning in release builds */
}