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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_compression_params ;

/* Variables and functions */
 int /*<<< orphan*/ * build_filter_chain_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_keep_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_stream *
build_filter_chain(fz_context *ctx, fz_stream *chain, pdf_document *doc, pdf_obj *fs, pdf_obj *ps, int num, int gen, fz_compression_params *params)
{
	return build_filter_chain_drop(ctx, fz_keep_stream(ctx, chain), doc, fs, ps, num, gen, params);
}