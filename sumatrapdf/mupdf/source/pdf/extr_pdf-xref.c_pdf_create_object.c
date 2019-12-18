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
struct TYPE_3__ {float type; int ofs; int num; int /*<<< orphan*/ * obj; int /*<<< orphan*/ * stm_buf; scalar_t__ stm_ofs; scalar_t__ gen; } ;
typedef  TYPE_1__ pdf_xref_entry ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int PDF_MAX_OBJECT_NUMBER ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* pdf_get_incremental_xref_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
pdf_create_object(fz_context *ctx, pdf_document *doc)
{
	/* TODO: reuse free object slots by properly linking free object chains in the ofs field */
	pdf_xref_entry *entry;
	int num = pdf_xref_len(ctx, doc);

	if (num > PDF_MAX_OBJECT_NUMBER)
		fz_throw(ctx, FZ_ERROR_GENERIC, "too many objects stored in pdf");

	entry = pdf_get_incremental_xref_entry(ctx, doc, num);
	entry->type = 'f';
	entry->ofs = -1;
	entry->gen = 0;
	entry->num = num;
	entry->stm_ofs = 0;
	entry->stm_buf = NULL;
	entry->obj = NULL;
	return num;
}