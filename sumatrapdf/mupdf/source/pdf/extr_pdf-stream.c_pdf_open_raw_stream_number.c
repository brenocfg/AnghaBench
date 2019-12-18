#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ stm_ofs; int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_xref_entry ;
struct TYPE_9__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* pdf_cache_object (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * pdf_open_raw_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int,int*,int*,scalar_t__) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,TYPE_2__*) ; 

fz_stream *
pdf_open_raw_stream_number(fz_context *ctx, pdf_document *doc, int num)
{
	pdf_xref_entry *x;
	int orig_num, orig_gen;

	if (num <= 0 || num >= pdf_xref_len(ctx, doc))
		fz_throw(ctx, FZ_ERROR_GENERIC, "object id out of range (%d 0 R)", num);

	x = pdf_cache_object(ctx, doc, num);
	if (x->stm_ofs == 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "object is not a stream");

	return pdf_open_raw_filter(ctx, doc->file, doc, x->obj, num, &orig_num, &orig_gen, x->stm_ofs);
}