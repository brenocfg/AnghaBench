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
struct TYPE_3__ {int /*<<< orphan*/  page_object_lists; int /*<<< orphan*/  hints_length; int /*<<< orphan*/  hints_s; int /*<<< orphan*/  linear_t; int /*<<< orphan*/  linear_n; int /*<<< orphan*/  linear_e; int /*<<< orphan*/  linear_o; int /*<<< orphan*/  linear_h1; int /*<<< orphan*/  linear_h0; int /*<<< orphan*/  linear_l; int /*<<< orphan*/  rev_renumber_map; int /*<<< orphan*/  renumber_map; int /*<<< orphan*/  gen_list; int /*<<< orphan*/  ofs_list; int /*<<< orphan*/  use_list; } ;
typedef  TYPE_1__ pdf_write_state ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_objects_list_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finalise_write_state(fz_context *ctx, pdf_write_state *opts)
{
	fz_free(ctx, opts->use_list);
	fz_free(ctx, opts->ofs_list);
	fz_free(ctx, opts->gen_list);
	fz_free(ctx, opts->renumber_map);
	fz_free(ctx, opts->rev_renumber_map);
	pdf_drop_obj(ctx, opts->linear_l);
	pdf_drop_obj(ctx, opts->linear_h0);
	pdf_drop_obj(ctx, opts->linear_h1);
	pdf_drop_obj(ctx, opts->linear_o);
	pdf_drop_obj(ctx, opts->linear_e);
	pdf_drop_obj(ctx, opts->linear_n);
	pdf_drop_obj(ctx, opts->linear_t);
	pdf_drop_obj(ctx, opts->hints_s);
	pdf_drop_obj(ctx, opts->hints_length);
	page_objects_list_destroy(ctx, opts->page_object_lists);
}