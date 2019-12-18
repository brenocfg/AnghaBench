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
 int /*<<< orphan*/  ID ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_memrnd (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int nelem (unsigned char*) ; 
 int /*<<< orphan*/  pdf_array_push_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_put_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_new_string (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pdf_obj *
new_identity(fz_context *ctx, pdf_document *doc)
{
	unsigned char rnd[32];
	pdf_obj *id;

	fz_memrnd(ctx, rnd, nelem(rnd));

	id = pdf_dict_put_array(ctx, pdf_trailer(ctx, doc), PDF_NAME(ID), 2);
	pdf_array_push_drop(ctx, id, pdf_new_string(ctx, (char *) rnd + 0, nelem(rnd) / 2));
	pdf_array_push_drop(ctx, id, pdf_new_string(ctx, (char *) rnd + 16, nelem(rnd) / 2));

	return id;
}