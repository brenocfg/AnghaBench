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
struct TYPE_3__ {int /*<<< orphan*/  contents; int /*<<< orphan*/  resources; } ;
typedef  TYPE_1__ pdf_pattern ;
typedef  int /*<<< orphan*/  fz_storable ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_drop_pattern_imp(fz_context *ctx, fz_storable *pat_)
{
	pdf_pattern *pat = (pdf_pattern *)pat_;
	pdf_drop_obj(ctx, pat->resources);
	pdf_drop_obj(ctx, pat->contents);
	fz_free(ctx, pat);
}