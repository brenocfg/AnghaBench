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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * pdf_get_bound_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pdf_filter_store(fz_context *ctx, void *doc_, void *key)
{
	pdf_document *doc = (pdf_document *)doc_;
	pdf_obj *obj = (pdf_obj *)key;
	pdf_document *key_doc = pdf_get_bound_document(ctx, obj);

	return (doc == key_doc);
}