#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char type; int /*<<< orphan*/  ofs; } ;
typedef  TYPE_2__ pdf_xref_entry ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_9__ {int /*<<< orphan*/  base; } ;
struct TYPE_11__ {TYPE_1__ lexbuf; int /*<<< orphan*/  file; } ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_2__* pdf_get_xref_entry (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/ * pdf_parse_ind_obj (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,TYPE_3__*) ; 

pdf_obj *
pdf_load_unencrypted_object(fz_context *ctx, pdf_document *doc, int num)
{
	pdf_xref_entry *x;

	if (num <= 0 || num >= pdf_xref_len(ctx, doc))
		fz_throw(ctx, FZ_ERROR_GENERIC, "object out of range (%d 0 R); xref size %d", num, pdf_xref_len(ctx, doc));

	x = pdf_get_xref_entry(ctx, doc, num);
	if (x->type == 'n')
	{
		fz_seek(ctx, doc->file, x->ofs, SEEK_SET);
		return pdf_parse_ind_obj(ctx, doc, doc->file, &doc->lexbuf.base, NULL, NULL, NULL, NULL);
	}
	return NULL;
}