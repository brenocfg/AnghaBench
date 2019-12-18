#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_5__ {TYPE_2__* chain; } ;
typedef  TYPE_1__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int /*<<< orphan*/  (* op_gs_begin ) (int /*<<< orphan*/ *,TYPE_2__*,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ExtGState ; 
 int /*<<< orphan*/  FLUSH_ALL ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_resource (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  filter_flush (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_filter_gs_begin(fz_context *ctx, pdf_processor *proc, const char *name, pdf_obj *extgstate)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_flush(ctx, p, FLUSH_ALL);
	if (p->chain->op_gs_begin)
		p->chain->op_gs_begin(ctx, p->chain, name, extgstate);
	copy_resource(ctx, p, PDF_NAME(ExtGState), name);
}